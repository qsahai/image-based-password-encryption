#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#ifndef LOGIN_H
#define LOGIN_H


class loginHandler {


    private:

        // count lines of a file (-1 because of image name) without using external libraries
        int getLineCount();

        // returns true if username is already in databank
        bool checkForUsername();

    
    public:

        string username, password;

        // handler function to begin registration process
        void attemptRegistration();

        // handler function to begin login process
        bool attemptLogin();

        
        string getUsername();


};


#endif
