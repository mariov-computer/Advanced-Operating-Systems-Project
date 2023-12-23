#include "shell.h"
#include "filesys.h"
#include "block.h"
#include "sdisk.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
using namespace std;



//Nov.7 class lecture (arrived late)
Shell::Shell(string filename, int numberofblocks, int blocksize): Filesys(filename, numberofblocks, blocksize){

}



// Nov.7 class lecture
int Shell::dir(){
  vector<string> files = ls();
  for(int i = 0; i < files.size(); i++){
    cout << files[i] << endl;
  }
  return 1;
}


/*video from email
int Shell::add(string file, string buffer){
  int error = newfile(file);
  if(error < 1){
    cout << "Sorry no good" << endl;
    return 0;
  }
  vector<string> blocks = block(buffer, getblocksize());
  for(int i = 0; i < blocks.size(); i++){
    addblock(file, blocks[i]);
  }
  return 1;
}
*/

//Nov 7th class
int Shell::add(string file, string buffer){
  int b = getfirstblock(file);
  if(b !=1 ){
    cout << "file exists";
    return 0;

  }
  else{
    newfile(file);
    vector<string> blocks = block(buffer, getblocksize());
    for(int i = 0; i < blocks.size(); i++)
    {
      addblock(file, blocks[i]);

    }

  }
  return 1;
}

int Shell::del(string file){
  while(getfirstblock(file) > 0){
    delblock(file, getfirstblock(file));
  }
  if(getfirstblock(file) == 0){
    rmfile(file);
    return 1;
  }
  else return 0;

}

int Shell::copy(string file1, string file2){
  int b = getfirstblock(file2);
  if(b >= 0){
    cout <<"destination file exists";
    return 0;
  }
  b = getfirstblock(file1);
  if(b==-1){
  cout << "source file does not exist";
  return 0;
  }

  newfile(file2);
  while (b != 0){
    string buffer;
    readblock(file1, b , buffer);
    addblock(file2, buffer);
    b = nextblock(file1, b);
  }
  return 1;
}

//type is very similar to copy
int Shell::type(string file){
  int b = getfirstblock(file);
if(b >= 0){
    cout <<"destination file exists";
    return 0;
  }
  b = getfirstblock(file);
  if(b==-1){
  cout << "source file does not exist";
  return 0;
  }

  newfile(file);


 
  while (b != 0){
    string buffer;
    readblock(file, b , buffer);
    cout << buffer;
    b = nextblock(file, b);
  }
  cout << endl;
  return 1;
}