#include "functions.h"

using namespace std;

int main()
{
    string fileName, keyFileName;
    char choice;

    // Loop until the file exists
    while (true) {
        cout << "Enter the file name to encrypt or decrypt (with extension): ";
        cin >> fileName;

        ifstream inputFile(fileName);  // Check if the file exists
        if (!inputFile) {
            cerr << "Error: The file '" << fileName << "' does not exist. Please try again." << endl;
        } else {
            break;  // Exit the loop if the file exists
        }
    }

    // Prompt for encryption or decryption choice
    while (true) {
        cout << "Do you want to encrypt or decrypt the file? (e/d): ";
        cin >> choice;

        if (choice == 'e') {  // Encryption
            vector<unsigned char> key;
            generateKey(fileName, key);  // Generate the key
            processFile(fileName, key, true);  // Encrypt the file
            break;
        } else if (choice == 'd') {  // Decryption
            cout << "Enter the key file name: ";
            cin >> keyFileName;
            vector<unsigned char> key;
            readKeyFromFile(keyFileName, key);  // Read the key
            processFile(fileName, key, false);  // Decrypt the file
            deleteKeyFile(fileName);  // Delete the key file
            break;
        } else {
            cerr << "Invalid choice! Please enter 'e' or 'd'." << endl;
        }
    }

    return 0;
}
