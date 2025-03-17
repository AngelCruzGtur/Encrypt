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
