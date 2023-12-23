#include "passwordfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//This is part of LAB #1
using namespace std;

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