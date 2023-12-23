#include "filesys.h"
#include "sdisk.h"
#include "block.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
using namespace std;



//filesys code from Oct 3rd tuesday class
int Filesys::fssynch(){
    //write root to block 1
    ostringstream outstream;
    for(int i = 0; i < filename.size(); i++){

        outstream << filename[i] << " "<< firstblock[i] << "";

    }

    string buffer = outstream.str();

    vector<string> blocks = block(buffer, getblocksize());
    putblock(1, blocks[0]);
    ostringstream outstream2;
    for(int i = 0; i <fat.size(); i++)
    {
        outstream2 << fat[i] <<" ";
    }
//setblocksize or getblocksize?
    string buffer2 = outstream2.str();
    vector<string> blocks2 = block(buffer2, getblocksize());
    for(int i = 0; i <blocks2.size(); i++){
        putblock(2+i, blocks2[i]);
    }

    return 1;
}


Filesys::Filesys(string diskname, int numberofblocks, int blocksize): Sdisk(diskname, numberofblocks, blocksize){
    //set attributes over here
    this->rootsize = getblocksize() / 11;
    this->fatsize = 5 * getnumberofblocks() / getblocksize() +1;
    string buffer;
    int code = getblock(1, buffer);
    if(buffer[0] == '#')
    {
        //no file system
        buildfs();
        fssynch();

    }
    else{
        readfs();
    }
}


//October 5th Thursday class: Still part of project 2
int Filesys::buildfs(){
    for(int i = 0; i < rootsize; i++){
        filename.push_back("XXXXX");
        firstblock.push_back(0);
    }
    //build fattfirstblock(file) >= )
    fat.push_back(fatsize + 2);
    fat.push_back(-1);
    for(int i = 0; i < fatsize; i++){
        fat.push_back(-1);
    }
    for(int i = fatsize+2; i < getnumberofblocks(); i++){
        fat.push_back(i+1);
    }
    fat[fat.size()-1] = 0 ; //not sure how to change the zero
    return 1;
}


int Filesys::readfs(){
    string buffer;
    int code = getblock(1, buffer);
    if(code == 0){
        cout << "could not read root\n";
        return 0;

    }
    istringstream istream;
    istream.str(buffer);

    for(int i = 0; i < rootsize; i++){
        string s;
        int x;
        istream >> s >> x;
        filename.push_back(s);
        firstblock.push_back(x);
    }
    //read fat
 string buffer2;
 for(int i = 0; i < fatsize; i++){
    getblock(2+i , buffer);
    buffer2 += buffer;
}
istringstream istream2;
istream2.str(buffer2);

for(int i = 0; i < getnumberofblocks(); i++){
    int x;
    istream2 >> x;
    fat.push_back(x);
}
return 1;
}


//Tuesday class - october 10th
int Filesys::getfirstblock(string file){
    //return first block number of file
    //-1 if file does not exist
    for(int i = 0; i < filename.size(); i++){
        if(filename[i] == file)
        return firstblock[i];
    }
    return -1;
}
//Tuesday class - october 10th
int Filesys::newfile(string file){
    if(getfirstblock(file) >= 0 ){
        cout << "file already exists.NEWFILE\n" << endl;
        return 0;
    }
    else{
        for(int i = 0; i < filename.size(); i++){
            if (filename[i]== "XXXXX"){
                filename[i] = file;
                firstblock[i] = 0;
                fssynch();
                return 1;
            }
        }

    }
    //fssynch();
    //return 0;
    return 1;
}
//Tuesday class - october 10th
int Filesys::rmfile(string file){
    int block = getfirstblock(file);
    if(block > 0){
        cout << "file is not empty\n";
        return 0;//null
    }
    if( block == -1){
        cout <<"file does not exist\n";
        return 0;// is this a null?
    }
    for(int i = 0; i < filename.size(); i++){
        if(filename[i] ==  file){
            filename[i] = "XXXXX";
            firstblock[i] = 0; // not possible for a null
            fssynch();//fssynch here
            return 1;
        }
    }
    return 0; //here goes nothing
}

//Thursday class - OCtober 12th
int Filesys::addblock(string file, string buffer)
{
    //add buffer data
    int first = getfirstblock(file); //error 
    if(first == -1){
        cout << "file does not exist!ADDBLOCK\n";
        return 0;
    }
    int allocate = fat[0];
    if (allocate == 0){
        cout << "no space left\n";
        return 0;
    }
    //update free list
    fat[0] = fat[fat[0]];
    fat[allocate]  = 0;
    if(first == 0){
        //update
        for(int i = 0; filename.size(); i++){
            if(filename[i] == file)//error
            {
                firstblock[i] = allocate;
                break;
            }
        }
    }
    else{
        int block = first;
        while(fat[block] != 0){
            block = fat[block];
        }
        //fat block = 0
        fat[block] = allocate;

    } // end else
    putblock(allocate, buffer);
    fssynch();
    return 1;
//Can't figure out where to put fssynch
    
}



//Tuesday Oct. 17th - Midway point of semester
//private function in Filesys
bool Filesys::fileblock(string file, int block){
    //true if
    int b = getfirstblock(file);
    if(b == -1){
        cout << "no such file\n";
        return false;
    }
    if(block ==0){
        return false;
    }
    if(b==block){
        cout <<"it is the first block\n";
        return true;
    }
    if(b==0){
        cout << "file is empty\n";
        return false;
    }
    while(b != 0){
        if(b == block){
        return true;}

    }
    return false;
}


int Filesys::readblock(string file, int blocknumber, string& buffer){
    if (fileblock(file, blocknumber)) { 
        getblock(blocknumber, buffer);
        return 1;
    }
    else{
        return 0;
    }

}

int Filesys::writeblock(string file, int blocknumber, string buffer){
    if (fileblock(file, blocknumber)) { 
        putblock(blocknumber, buffer);
        //return 1;
    }
    else{
        return 0;
    }

return 0; //here goes nothing
}

int Filesys::delblock(string file, int blocknumber){
    int deallocate = blocknumber;
    if(!fileblock(file, blocknumber)){
        cout <<"Blocknumber does not belong to file.\n";
        return 0;
    }
    int b = getfirstblock(file);
    if(blocknumber == b){
        //deleting first block
        for(int i = 0; i<filename.size(); i++){
            if(filename[i]==file);
            firstblock[i] = fat[b];
        }
    }
    else{
        //deleting block not first
        while(fat[b] != blocknumber){
            b = fat[b];
        }
        //fat[b] == blocknumber
        fat[b] = fat[blocknumber];
    }//end else
    fat[blocknumber] = fat[0];
    fat[0] = blocknumber;
    fssynch();
    return 1;

}

//Week 9 - October 24th
int Filesys::nextblock(string file, int blocknumber){
if(fileblock(file, blocknumber))
return fat[blocknumber];
else{
return -1;
}
}

//new addition from Lab 6
vector<string> Filesys::ls()
{ vector <string> flist;
  for (int i=0; i<filename.size(); i++)
      {
        if (filename[i] != "XXXXX")
           {
             flist.push_back(filename[i]);
           }
      }
  return flist;
}