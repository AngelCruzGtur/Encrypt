# Encrypt

This project implements a simple **file encryption system** using the **XTEA (eXtended Tiny Encryption Algorithm)**. It demonstrates how to use a **256-bit encryption key** to securely encrypt and decrypt files, making it useful for educational purposes and learning about **block ciphers** and **key management**.

## Features

- **XTEA Encryption**: A block cipher that encrypts files using a 256-bit key.
- **File Padding**: Adds padding to ensure the file length is a multiple of 8 bytes.
- **Checksum**: A simple XOR-based checksum is used to verify data integrity.
- **Key Generation**: A **random 256-bit key** is generated for encryption.
- **Key Management**: The program allows for secure generation and usage of encryption keys.

## How to Use

1. **Clone this repository**:
   ```bash
   git clone https://github.com/AngelCruzGtur/Encrypt.git
