#include "shell.h"
#include "filesys.h"
#include "block.h"
#include "sdisk.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
using namespace std;


//Week 12 of the fall semester - officially Lab#7 on the website
Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile): Filesys(diskname, numberofblocks, blocksize)
{
    this -> flatfile = flatfile;
    this -> indexfile = indexfile;
}

int Table::search(string value){
    int block = indexsearch(value);
    if (block == 0){
        cout << "not found at all" << endl;
        return 0;

    }
    else{
        string buffer;
        readblock(flatfile, block, buffer);
        cout << buffer;
        return 1;

    }
}

//Nov 16th - 4610 Lab#7 continued
int Table::build_table(string input_file){
    newfile(flatfile);
    newfile(indexfile);
    ifstream infile;
    infile.open(input_file.c_str());
    ostringstream ostream;
    string rec;

    getline(infile,rec);
    while(infile.good()){
        string key = rec.substr(0,5);
        vector<string> b = block(rec, getblocksize());
        int n = addblock(flatfile, b[0]);
        ostream << key << " " << n << " ";
        getline(infile, rec);
    }
    ostream << "kangaroo" << " " << 0 << " ";
    string ibuffer = ostream.str();
    vector<string> blocks = block(ibuffer, getblocksize());
    for (int i = 0; i < blocks.size(); i++){
        addblock(indexfile, blocks[i]);
    }
    return 1;
}

//indexfile : key block key block key blockk .... kangaroo 0
int Table::indexsearch(string value){
    string buffer;
    int b = getfirstblock(indexfile);
    while(b != 0){
        string buff;
        readblock(indexfile, b, buff);
        buffer += buff;
        b = nextblock(indexfile, b);
        }
        istringstream istream;
        istream.str(buffer);
        string k; int bl;
        istream >> k >> bl; //I just read the first index record

        while(k != "kangaroo"){
            if(k == value){
            return bl;
            }
            istream >> k >> bl;
        }
        return 0;
}