#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <sstream>
#include <algorithm>

void generateSecureKey(std::vector<unsigned char>& key);  // Function to generate a secure random key
void xtea_process(std::vector<unsigned char>& data, const std::vector<unsigned char>& key, bool encrypt);  // XTEA encryption and decryption function
void deriveKey(const std::string& password, std::vector<unsigned char>& derivedKey);  // Derive a key from a password using a simple hash
unsigned char calculateChecksum(const std::vector<unsigned char>& data);  // Function to calculate a simple checksum for integrity
bool verifyChecksum(const std::vector<unsigned char>& data, unsigned char checksum);  // Function to verify the checksum
void generateKey(const std::string& fileName, std::vector<unsigned char>& key);  // Key generation and file saving
void readKeyFromFile(const std::string& keyFileName, std::vector<unsigned char>& key);  // Load the key from a file
void processFile(const std::string& fileName, const std::vector<unsigned char>& key, bool encrypt);  // Encrypt or decrypt the file
void deleteKeyFile(const std::string& fileName);  // Securely delete the key file
void secureDeleteFile(const std::string& fileName);  // Overwrite and delete the key file

#endif
