#include "functions.h"

using namespace std;

// Secure random key generation using std::random_device
void generateSecureKey(vector<unsigned char>& key)
{
    std::random_device rd;  // Use secure random device
    std::uniform_int_distribution<unsigned char> dist(0, 255);  // Generate bytes in range 0-255

    for (size_t i = 0; i < 32; ++i) {  // Generate a 32-byte (256-bit) key
        key.push_back(dist(rd));
    }
}

// Padding the data to make the size multiple of 8 bytes (for XTEA)
void padData(std::vector<unsigned char>& data) {
    size_t paddingRequired = 8 - (data.size() % 8);
    if (paddingRequired == 8) {
        return;  // No padding needed if data is already a multiple of 8
    }

    // Pad the data with 0x00 (or any other byte that won't conflict with the actual data)
    for (size_t i = 0; i < paddingRequired; ++i) {
        data.push_back(0x00);
    }
}

// Removing padding after decryption (assuming padding is 0x00)
void unpadData(std::vector<unsigned char>& data) {
    while (!data.empty() && data.back() == 0x00) {
        data.pop_back();  // Remove the padding (0x00)
    }
}

// XTEA encryption/decryption function
void xtea_process(std::vector<unsigned char>& data, const std::vector<unsigned char>& key, bool encrypt)
{
    uint32_t state[16] = {0};

    // Load the key into the state
    for (int i = 0; i < 8; ++i) {
        state[i] = (key[i * 4] << 24) | (key[i * 4 + 1] << 16) | (key[i * 4 + 2] << 8) | key[i * 4 + 3];
    }

    // Initialize counter (nonce) values for XTEA
    state[12] = 0;  // Set your nonce and counter values here
    state[13] = 0;
    state[14] = 0;
    state[15] = 0;

    for (size_t i = 0; i < data.size(); i += 8) {
        uint32_t v0 = (data[i] << 24) | (data[i + 1] << 16) | (data[i + 2] << 8) | data[i + 3];
        uint32_t v1 = (data[i + 4] << 24) | (data[i + 5] << 16) | (data[i + 6] << 8) | data[i + 7];

        uint32_t sum = encrypt ? 0 : 0xC6EF3720;  // Start the sum for decryption or encryption
        uint32_t delta = 0x9E3779B9;
        uint32_t rounds = 32;

        for (uint32_t round = 0; round < rounds; ++round) {
            if (encrypt) {
                v0 += (((v1 << 4) + state[0]) ^ (v1 + sum) ^ ((v1 >> 5) + state[1]));
                sum += delta;
                v1 += (((v0 << 4) + state[2]) ^ (v0 + sum) ^ ((v0 >> 5) + state[3]));
            } else {
                v1 -= (((v0 << 4) + state[2]) ^ (v0 + sum) ^ ((v0 >> 5) + state[3]));
                sum -= delta;
                v0 -= (((v1 << 4) + state[0]) ^ (v1 + sum) ^ ((v1 >> 5) + state[1]));
            }
        }

        data[i] = (v0 >> 24) & 0xFF;
        data[i + 1] = (v0 >> 16) & 0xFF;
        data[i + 2] = (v0 >> 8) & 0xFF;
        data[i + 3] = v0 & 0xFF;
        data[i + 4] = (v1 >> 24) & 0xFF;
        data[i + 5] = (v1 >> 16) & 0xFF;
        data[i + 6] = (v1 >> 8) & 0xFF;
        data[i + 7] = v1 & 0xFF;
    }
}

// Simple hash-like function to derive a key (for educational purposes)
unsigned int simple_hash(const string& input) {
    unsigned int hash = 2166136261U;
    for (size_t i = 0; i < input.size(); ++i) {
        hash ^= input[i];
        hash *= 16777619;
    }
    return hash;
}

void deriveKey(const string& password, vector<unsigned char>& derivedKey) {
    unsigned int hashValue = simple_hash(password);
    derivedKey.clear();

    // Convert hash value to a byte vector
    for (size_t i = 0; i < 32; ++i) {
        derivedKey.push_back(static_cast<unsigned char>(hashValue & 0xFF));  // Use the lower 8 bits
        hashValue >>= 8;  // Shift to get the next byte
    }
}

// Simple checksum calculation for integrity verification
unsigned char calculateChecksum(const vector<unsigned char>& data)
{
    unsigned char checksum = 0;
    for (auto byte : data) {
        checksum ^= byte;  // XOR each byte to get a simple checksum
    }
    return checksum;
}

// Verify if the checksum of the data matches the provided checksum
bool verifyChecksum(const vector<unsigned char>& data, unsigned char checksum)
{
    return calculateChecksum(data) == checksum;  // Check if the checksum matches
}

// Function to generate the encryption key and store it in a file
void generateKey(const string& fileName, vector<unsigned char>& key)
{
    generateSecureKey(key);  // Use the secure key generation

    ofstream keyFile(fileName + ".key", ios::binary);  // Open key file to save
    if (!keyFile) {
        cerr << "Error: Could not create key file!" << endl;
        return;
    }

    // Write the key to the file in hex format
    for (size_t i = 0; i < key.size(); ++i) {
        keyFile << hex << uppercase << setw(2) << setfill('0') << (int)key[i] << " ";
    }
    keyFile.close();

    cout << "Key file '" << fileName + ".key" << "' has been created." << endl;
}

// Load the encryption key from a file
void readKeyFromFile(const string& keyFileName, vector<unsigned char>& key)
{
    ifstream keyFile(keyFileName, ios::binary);  // Open the key file
    if (!keyFile) {
        cerr << "Error: Could not open key file!" << endl;
        return;
    }

    key.clear();
    string hexString;
    
    // Read each hex string from the file and convert it to bytes
    while (keyFile >> hex >> hexString) {
        if (hexString.length() == 2) {
            transform(hexString.begin(), hexString.end(), hexString.begin(), ::toupper);  // Convert to uppercase
            unsigned char byte = static_cast<unsigned char>(stoi(hexString, nullptr, 16));  // Convert hex to byte
            key.push_back(byte);  // Add byte to key
        } else {
            cerr << "Error: Invalid hex string in key file: " << hexString << endl;
            return;
        }
    }
    keyFile.close();

    if (key.empty()) {
        cerr << "Error: Key file is empty or invalid!" << endl;
        return;
    }

    cout << "Key file '" << keyFileName << "' has been loaded." << endl;
}

// Encrypt or decrypt the file using the key
void processFile(const std::string& fileName, const std::vector<unsigned char>& key, bool encrypt)
{
    // Read the file into memory
    std::ifstream file(fileName, std::ios::binary);
    std::vector<unsigned char> fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (fileContent.empty()) {
        std::cerr << "Error: The file is empty!" << std::endl;
        return;
    }

    // Pad the data before encryption (only if encrypting)
    if (encrypt) {
        padData(fileContent);  // Add padding during encryption
    }

    // Encrypt or decrypt the file content using XTEA
    xtea_process(fileContent, key, encrypt);

    // Unpad the data after decryption (only if decrypting)
    if (!encrypt) {
        unpadData(fileContent);  // Remove padding during decryption
    }

    // Write the modified data back to the file
    std::ofstream outFile(fileName, std::ios::binary);
    outFile.write(reinterpret_cast<char*>(fileContent.data()), fileContent.size());
    outFile.close();

    std::cout << "File has been " << (encrypt ? "encrypted" : "decrypted") << " successfully." << std::endl;
}
void deleteKeyFile(const string& fileName)
{
    string keyFileName = fileName + ".key";  // Construct key file name
    if (remove(keyFileName.c_str()) == 0) {
        cout << "Key file has been deleted." << endl;
    } else {
        cout << "No key file found to delete." << endl;
    }
}