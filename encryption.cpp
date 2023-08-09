#include "averageColor.cpp"
#include <iostream>
#include <cmath>
using namespace std;


// use this to convert the character in a string after encryption to print/write
unsigned int convert (char ch) {
    return static_cast<unsigned int>(ch) & 0xFF;
}


class passwordEntry {


    private:

        // one variable each for an encrypted/decrypted password
        string encryptedPW;

        // private key to be determined by the target pixel function
        unsigned int key;

        void encrypt (string password, unsigned int avg) {

            key = findTarget(image, avg);
            unsigned int RGB[3];

            // encryption code
            if ((image.rows * image.cols) % 3 == 0) {

                // RGB
                RGB[0] = R(key);
                RGB[1] = G(key);
                RGB[2] = B(key);
                //cout << "RGB" << endl;

            } else if ((image.rows * image.cols) % 3 == 1) {

                // BRG
                RGB[0] = B(key);
                RGB[1] = R(key);
                RGB[2] = G(key);
                //cout << "BRG" << endl;

            } else {

                // GBR
                RGB[0] = G(key);
                RGB[1] = B(key);
                RGB[2] = R(key);
                //cout << "GBR" << endl;

            }

            // cout << "Target: " << hex << key << dec << endl;
            // cout << "Sequence: " << hex << RGB[0] << dec << " " << hex << RGB[1] << dec << " " << hex << RGB[2] << dec << endl;
            // cout << "Password elements:" << endl;

            // xor the key sequence with password using the buffer array
            int i = 0;
            for (i; i < password.length(); i++) {
                // cout << hex << RGB[(i + 3) % 3] << dec << endl;                 // key fragment
                // cout << hex << (unsigned int)password[i] << dec << endl;        // character in password
                password[i] = (password[i] ^ RGB[(i + 3) % 3]);
            }


            /*
            
            the former bit of code was made to address a "bug" where casting the contents of the 
            buffer to a char results in the correct output, however every other byte before the
            value is flipped to 1.
            
            for example, if the correct buffer output is 0xF9, casting it
            to a char results in it changing to 0xFFFFFFF9.
            
            the cause of this is for the unsigned char and char type flipping every bit after the 7th
            whenever bit 7 is 1, instead of signing the 7th bit only. and it carries over in trying to
            AND it with 0xFF, as it constantly re-signs itself as long as the 7th bit is 1

            I've never encountered this so I'm storing it as an array of unsigned
            ints instead in the main 
            
            */

            //cout << password << endl;
            
            this->finalOutput = password;

        }


    public:

        // output
        string finalOutput;

        // image's average color
        unsigned int avg;
        Mat image;

        // (starting password, encrypt/decrypt choice)
        void beginProcess (string enteredPW, string imagePath) {

            // set image source, key and encrypt
            this->image = imread("images/" + imagePath);
            avg = getAvg(image);
            encrypt(enteredPW, avg);

        }

        // simple get function after operations
        string getResult () {
            return finalOutput;
        }


};

