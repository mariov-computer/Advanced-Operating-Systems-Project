#include "sdisk.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;



//this is part of Lab#2 alongside sdisk.cpp and sdisk.h


int main()
//Thursday lecture 9/21
{
  Sdisk disk1("test1",16,32);
  string block1, block2, block3, block4;
  for (int i=1; i<=32; i++) block1=block1+"1";
  for (int i=1; i<=32; i++) block2=block2+"2";
  disk1.putblock(4,block1);
  disk1.getblock(4,block3);
  cout << "Should be 32 1s : ";
  cout << block3 << endl;
  disk1.putblock(8,block2);
  disk1.getblock(8,block4);
  cout << "Should be 32 2s : ";
  cout << block4 << endl;
}

