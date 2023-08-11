# login-system-using-image-based-password-encryption
This is a login system that utilizes an encryption algorithm based on specific pixel color values (via OpenCV) of a given image as a seed to encrypt passwords. 

### main.cpp and loginHandler.cpp
The system for the basic login structure. The user is asked to either log in or register a new account.
To register, the user inputs a username, password, and source image (found in the /images folder).
The login handler then checks if the username exists, and if not, encrypts the password (**encryption.cpp**) and writes it to the [username].txt file along with the image used.
When logging in, the user is asked for their username and password.
First, the handler checks to see if the username exists, then creates a separate array of unsigned integers which contains the encrypted characters of the password inputted at login and compares the amount of matching characters between it and the values stored in the user file.
(An array of unsigned integers was chosen over a simple comparison between two encrypted strings due to a bug where characters, even if unsigned, would always default to signing every bit after the 8th if the 8th bit was high. For example, if the correct hex value of a character after encryption was 0x8C, the character would be saved as 0xFFFFFF8C.)


A basic program I have created using the same encryption algorithm can be found here: https://github.com/qsahai/image-based-string-encryption
