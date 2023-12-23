#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//Begin by creating a class PasswordFile which has the following interface
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
// Encryption attempt #1
//nt PasswordFile::addpw(string newuser, string newpassword)
//{
  //  string enpasword = encrypt (newpassword)
//for (int i=0; i < user.size(); i++){
   // if (user[i] == newuser)
   // cout << "user exists" << endl;
//}

//}

//Also, create a main program to test your classes
int main()
{
    PasswordFile passfile("password.txt");
    passfile.addpw("dbotting", "123qwe");
    passfile.addpw("egomez", "qwerty");
    passfile.addpw("tongyu", "liberty");
    //write some lines to see if passwords match users
    passfile.addpw("pizza", "sandwich");
     passfile.addpw("burger", "moose");

    cout << "Enter username: ";
    string username;
    cin >> username;

    cout << "Enter password: ";
    string password;
    cin >> password;

    if (passfile.checkpw(username, password))
    {
        cout << "Access granted." << endl;
    }
    else
    {
        cout << "Access denied." << endl;
    }

    return 0;
}
