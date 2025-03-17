# Encrypt

This project implements a simple **file encryption system** using the **XTEA (eXtended Tiny Encryption Algorithm)**. It is designed to **encrypt and decrypt text files** using a **256-bit encryption key**. This project is primarily **for educational purposes** and demonstrates how to handle **file encryption**, **decryption**, **key management**, and **data integrity**.

## Features

- **XTEA Encryption**: A block cipher that encrypts files using a **256-bit key**.
- **File Padding**: Adds padding to ensure the file length is a multiple of 8 bytes for encryption.
- **Checksum**: A simple XOR-based checksum is used to verify data integrity.
- **Key Generation**: A **random 256-bit key** is generated for encryption.
- **Key Management**: The program allows for secure generation and usage of encryption keys.
- **Text File Support**: The encryption and decryption is designed to work with **text files**.

## How to Use

1. **Clone this repository**:
   ```bash
   git clone https://github.com/AngelCruzGtur/Encrypt.git
   cd Encrypt
   2. Compile the project:

   
2. After cloning the repository, compile the project using a C++ compiler (e.g., G++).

- For Linux/MacOS:
  ```
  g++ -std=c++11 main.cpp functions.cpp -o file_encryption
  ```

- For Windows using MinGW (make sure MinGW is installed):
  ```
  g++ -std=c++11 main.cpp functions.cpp -o file_encryption.exe
  ```

This will compile the source files `main.cpp` and `functions.cpp` and create an executable named `file_encryption` (or `file_encryption.exe` on Windows).

3. Run the program:

After compiling the program, run the executable:

- On Linux/MacOS:
  ```
  ./file_encryption
  ```

- On Windows:
  ```
  file_encryption.exe
  ```

4. Encrypt/Decrypt text files:

The program will prompt you to enter the name of the text file you want to encrypt or decrypt.

- If you are decrypting, provide the key file that was generated during encryption.

## Example Usage

- To encrypt a text file:
- Enter the name of the text file you want to encrypt.
- The program will generate a key and encrypt the file.

- To decrypt a text file:
- Provide the encrypted file and the key file used during encryption.

## Security Considerations

- XTEA is used for educational purposes and may not be suitable for production use due to known cryptographic weaknesses.
- Key management is critical for the system's security. Ensure that encryption keys are stored securely (e.g., in encrypted storage or hardware security modules).
- Data Integrity: The XOR-based checksum is not cryptographically secure. For improved security, consider using HMAC or a more secure checksum algorithm.

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). See the LICENSE file for more details.

## Contributing

Feel free to contribute to this project by opening issues or submitting pull requests. If you have any suggestions for improvements or bug fixes, please open an issue!

---
