#include "filesys.h"
#include "sdisk.h"
#include "block.h"
#include "shell.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
// this is the main program from Lab 6 on the website

using namespace std;

int main()
{
 //
 //This main program inputs commands to the shell.
 //It inputs commands as : command op1 op2
 //You should modify it to work for your implementation.
 //Let me try something as of Nov. 9th: CREATE A DISK1?????
  Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  fsys.newfile("file1");
  fsys.newfile("file2");



 //
 string s;
 string command="go";
 string op1,op2;

 while (command != "quit")
     {
       command.clear();
       op1.clear();
       op2.clear();
       cout << "$";
       getline(cin,s);
       int firstblank=s.find(' ');
       if (firstblank < s.length()) s[firstblank]='#';
       int secondblank=s.find(' ');
       command=s.substr(0,firstblank);
       if (firstblank < s.length())
         op1=s.substr(firstblank+1,secondblank-firstblank-1);
       if (secondblank < s.length())
         op2=s.substr(secondblank+1);
       if (command=="dir")
          {
            // use the ls function
           }
       if (command=="add")
          {
            // The variable op1 is the new file and op2 is the file data
           }
       if (command=="del")
          {
            // The variable op1 is the file
           }
       if (command=="type")
          {
            // The variable op1 is the file
           }
       if (command=="copy")
          {
            // The variable op1 is the source file and the variable op2 is the destination file.
           }
       if (command=="search")
          {
            // This is the command for Project 4
            // The variable op1 is the date
           }
       
      }

 return 0;
}