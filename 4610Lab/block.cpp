// This is supposedly part 2 of the project
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> block(string s, int b)
{
// blocks the buffer into a list of blocks of size b
// 1. how many blocks in vector
//2. copy strings to blocks
//3. fill the last block with #'s
vector<string> blocks;
int numberofblocks=0;

if (s.length() % b == 0) 
   { numberofblocks= s.length()/b;
   }
else 
   { numberofblocks= s.length()/b +1;
   }

//copy s to vector
string tempblock;
for (int i=0; i<numberofblocks; i++)

    { tempblock=s.substr(b*i,b);
      blocks.push_back(tempblock);
    }

int lastblock=blocks.size()-1;

for (int i=blocks[lastblock].length(); i<b; i++)
    { blocks[lastblock]+="#";
    }

return blocks;
}

