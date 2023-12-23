#ifndef TABLE_H
#define TABLE_H

#include "filesys.h"
#include "sdisk.h"
#include "block.h"
#include "shell.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class Table : public Filesys
{
public :
Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile);
int build_table(string input_file);
int search(string value);
private :
string flatfile;
string indexfile;
int indexsearch(string value);
//int numberofrecords;
//FileSys filesystem;
};
#endif