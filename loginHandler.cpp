#include "loginHandler.h"


class logInHandler {


    private:

        bool checkForUsername (string username) {
    
            ifstream unFile;
            unFile.open("data/" + username + ".txt");
            if (unFile) {
                return true;
            } else {
                return false;
            }

        }


    public:

        string username, password;

        void attemptRegistration(string un, string pw) {
            
            this->username = un;
            this->password = pw;

            if (this->checkForUsername(username) == true) {         // check for file with username

                cout << "\nUsername is already taken. Try a different one." << endl;

            } else {                                                // username is available
                
                // create file with new login
                ofstream file;
                file.open("data/" + username + ".txt");
                file << username << endl << password;
                file.close();

                cout << "\nAccount creation successful. Log in to access acount." << endl;

            }

        }

        bool attemptLogin (string un, string pw) {

            this->username = un;
            this->password = pw;
            string readun, readpw;

            // the function will read the file named after the username
            ifstream read("data/" + username + ".txt");
            getline(read, readun);
            getline(read, readpw);

            if (readun == username && readpw == password) {
                return true;
            } else {
                return false;
            }

        }


        string getUsername () {
            return this->username;
        }

};

