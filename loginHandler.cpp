#include "loginHandler.h"
#include "encryption.cpp"
#include <iostream>
#include <fstream>
using namespace std;


class logInHandler {


    private:


        // read file and return line count (-1 for )
        int getLineCount (string filePath) {
            
            int lineCount = 0;
            char c;
            ifstream lineCounter("data/" + username + ".txt");
            while(lineCounter.get(c)) {
                if (c == '\n') {
                    lineCount++;
                }
            }
            lineCounter.close();

            return (lineCount - 1);

        }


        // return true if username is already in databank
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
        passwordEntry attempt;

        void attemptRegistration(string un, string pw, string imagePath) {
            
            string finalPW;     // initialize encrypted password

            this->username = un;
            this->password = pw;

            // array to store encrypted data to be printed as hex value
            unsigned int PWArray[password.length()];

            if (this->checkForUsername(username) == true) {         // check for file with username

                cout << "\nUsername is already taken. Try a different one." << endl;

            } else {                                                // username is available
                
                // create file with new login
                ofstream file;
                file.open("data/" + username + ".txt");
                // cout << "Opened data/" + username + ".txt" << endl;

                // encrypt password
                attempt.beginProcess(password, imagePath);
                // cout << "Password encrypted" << endl;
                finalPW = attempt.getResult();

                file << imagePath << endl;

                // for loop for each character of the password
                for (int i = 0; i < password.length(); i++) {
                    PWArray[i] = convert(finalPW[i]);
                    file << hex << PWArray[i] << dec << endl;
                }
    
                file.close();

                cout << "\nAccount creation successful. Log in to access account." << endl;

            }

        }


        bool attemptLogin (string un, string pw) {

            this->username = un;
            this->password = pw;

            // entered string to compare to the read encrypted password
            string finalPW;
            
            // array to store encrypted data to be read as hex value
            unsigned int PWArray[password.length()];

            // read file to find image
            string imagePath;

            // the function will read the file named after the username
            ifstream read("data/" + username + ".txt");
            int lineCount = getLineCount(username);
            // cout << "Lines: " << lineCount << endl;

            // read image filepath, then read each line after for array elements
            getline(read, imagePath);
            // cout << imagePath << endl;
            for (int i = 0; i < lineCount; i++) {
                read >> hex >> PWArray[i] >> dec;
                // cout << hex << PWArray[i] << dec << endl;
            }
            read.close();

            attempt.beginProcess(password, imagePath);
            finalPW = attempt.getResult();
            
            // count matching elements and return true if matching elements = password length
            int compCount = 0;
            for (int i = 0; i < lineCount; i++) {
                if (PWArray[i] == convert((unsigned int)finalPW[i])) {
                    compCount++;
                }
            }

            if (compCount == lineCount) {
                return true;
            } else {
                return false;
            }


        }


        string getUsername () {
            return this->username;
        }

};

