#ifndef PASSWORDFILE_H
#define PASSWORDFILE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class PasswordFile{
public:
    PasswordFile(string filename);
    void addpw(string newuser, string newpassword);
    bool checkpw(string user, string passwd);
private:
    string filename;
    vector<string> user;
    vector<string> password;

    void readFromFile();
    void synch();

};
#endif

