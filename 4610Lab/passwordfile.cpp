#include <vector>
#include "passwordfile.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class PasswordFile
{
public:
    PasswordFile(string filename)
    {
        this->filename = filename;
        readFromFile();
    }

    void addpw(string newuser, string newpassword)
    {
        user.push_back(newuser);
        password.push_back(newpassword);
        synch();
    }

    bool checkpw(string user, string passwd)
    {
        for (size_t i = 0; i < this->user.size(); ++i)
        {
            if (this->user[i] == user && this->password[i] == passwd)
            {
                return true;
            }
        }
        return false;
    }

private:
string filename;
    vector<string> user;
    vector<string> password;

    void readFromFile()
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(' ');
            if (pos != string::npos)
            {
                user.push_back(line.substr(0, pos));
                password.push_back(line.substr(pos + 1));
            }
        }
    }

    void synch()
    {
        ofstream file(filename);
        if (!file)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (size_t i = 0; i < user.size(); ++i)
        {
            file << user[i] << " " << password[i] << endl;
        }
    }
};