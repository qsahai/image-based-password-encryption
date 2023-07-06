#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class loginHandler {


    private:

        bool checkForUsername();

    
    public:

        string username, password;

        void attemptRegistration();
        bool attemptLogin();
        string getUsername();


};

