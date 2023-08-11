# login-system-using-image-based-password-encryption
This is a login system that utilizes an encryption algorithm based on specific pixel color values (via OpenCV) of a given image as a seed to encrypt passwords.

To make, your system must have CMake and OpenCV (the makefile requires OpenCV version 2.8.4 or later but you are permitted to change it). Then, enter the terminal commands:

> cmake .

> make

(the cmake function only needs to be entered once even if you must rebuild the program)

### main.cpp and loginHandler.cpp
The system for the basic login structure. The user is asked to either log in or register a new account.

To register, the user inputs a username, password, and source image (found in the /images folder).

The login handler then checks if the username exists, and if not, encrypts the password (**encryption.cpp**) and writes it to the [username].txt file along with the image used.

When logging in, the user is asked for their username and password.

First, the handler checks to see if the username exists, then creates a separate array of unsigned integers which contains the encrypted characters of the password inputted at login and compares the amount of matching characters between it and the values stored in the user file.

(An array of unsigned integers was chosen over a simple comparison between two encrypted strings due to a bug where characters, even if unsigned, would always default to signing every bit after the 8th if the 8th bit was high. For example, if the correct hex value of a character after encryption was 0x8C, the character would be saved as 0xFFFFFF8C.)

### encryption.cpp
This contains the password entry object which has functions to find the average color of a chosen image (given by the user in the register function and a user file in the login function) to locate a "target pixel" to grab a key sequence from its RGB values and, depending on the total pixel count, shifts the individual R, B, and B values around to use as an encryption sequence for the chosen password.

Specifically, if the target image contains an even amount of pixels, the method of traversal to find the target pixel ("Type 1") will involve reading through the image row-by-row to the right and downward. If the total pixel count is odd, the traversal ("Type 2") will read column-to-column downward and to the right.

The key sequence RGB order is as follows:

if total % 3 = 0: RGB if total % 3 = 1: BRG if total % 3 = 2: GBR

The sequence will repeat for as many characters in the password (for example, if there are 5 characters with total % 3 = 1, they will be XOR-ed with the sequence in the order BRGBR).

A standalone version of this part of the project can be found here: https://github.com/qsahai/image-based-string-encryption

### averageColor.cpp
This contains the functions to obtain the average hex color of an image with arbitrary dimensions via OpenCV, then finds a target pixel color by traversing the image either by rows or columns first, depending on if the image's total pixel count is even or odd, respectfully.

A standalone version of this part of the project can be found here: https://github.com/qsahai/average-color-pixel-finder
