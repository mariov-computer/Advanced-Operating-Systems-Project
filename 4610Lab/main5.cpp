#include "filesys.h"
#include "sdisk.h"
#include "block.h"
#include "shell.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
//GIVEN MAIN PROGRAM FROM LAB 8 LINK ON WEBSITE

using namespace std;

int main()
{
 //CHECK FOR MarioValdez.tar
 //This main program inputs commands to the shell.
 //It inputs commands as : command op1 op2
 //You should modify it to work for your implementation.
 //GIVEN MAIN PROGRAM FROM LAB 8, this is all that's left
 Sdisk sdisk = Sdisk("sdisk.txt",256,128);
 Filesys fsys = Filesys("sdisk.txt",256,128);
 Shell shell = Shell("sdisk.txt",256,128);
 Table table = Table("sdisk.txt",256,128, "flatfile.txt", "indexfile.txt");
 table.build_table("data.txt");

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
       if (command=="search")
          {
            // The variable op1 is the date
           }
       if (command=="add")
          {
            // The variable op1 is the new file
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
       
      }

 return 0;
}