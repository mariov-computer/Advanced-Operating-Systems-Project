#include "sdisk.h"
#include "block.h"
#include "filesys.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
    this->diskname = diskname;
    this->numberofblocks = numberofblocks;
    this->blocksize = blocksize;
    ifstream infile;
    infile.open(diskname.c_str());

    bool check = infile.good();
    infile.close();
    if(check){
        if(checkfile()) //verify disk is rightsize
        {
            cout << "disk has been verified" << endl;
            return;
        }
    }
    else{
        //create disk
        cout << "creating disk" << endl;
        ofstream outfile;
        outfile.open(diskname.c_str());
        for(int i = 0; i << numberofblocks*blocksize; i++)
        {
            outfile.put('#');
        }
    }
    return;
}
bool Sdisk::checkfile(){
    int count = 0;
    ifstream infile;
    infile.open(diskname.c_str());
    char c = infile.get();  
   // char c;
   
    while (infile.good())      
    {
       
        count++;
        c = infile.get();
        
    }
    if(count = numberofblocks*blocksize){
        return true;
    }
    else{
        return false;
    }


        
}


int Sdisk::getblock(int blocknumber, string& buffer){
    buffer.clear();
    if((blocknumber < 0) or (blocknumber >= blocksize)){
        cout << blocknumber << "is out of range" << endl;
        return 0;
    } 
    fstream iofile;
    iofile.open(diskname.c_str(), ios::in | ios::out);
    iofile.seekg(blocknumber * blocksize);

    for (int i = 0; i < blocksize; i++ ){
        char c = iofile.get();
        buffer += c;
        //iofile.put(buffer[i]);
    }
    return 1;
    }


    int Sdisk::putblock(int blocknumber, string buffer){
    //buffer.clear();
    if((blocknumber < 0) or (blocknumber >= blocksize)){
        cout << blocknumber << "is out of range" << endl;
        return 0;
    } 
    fstream iofile;
    iofile.open(diskname.c_str(), ios::in | ios::out);
    iofile.seekp(blocknumber * blocksize);

    for (int i = 0; i < blocksize; i++ ){
       // char c = iofile.get();
        //buffer += c;
        iofile.put(buffer[i]);
    }
    return 1;
}

int Sdisk::getnumberofblocks(){
    return numberofblocks;
}

int Sdisk::getblocksize(){
    return blocksize;
}

