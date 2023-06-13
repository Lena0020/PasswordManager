//
// Created by Lena on 27/05/2023.
//

#ifndef PROJECT_ENCRYPTIONSERVICE_H
#define PROJECT_ENCRYPTIONSERVICE_H


#include <string>
/**
 * @class EncryptionService
 * @brief Provides encryption and decryption functionality for strings.
 *
 * The EncryptionService class provides static methods to encrypt and decrypt strings
 * using a main password. It allows for securing sensitive data by converting it into
 * an encrypted format and restoring it back to its original form.
 */
class EncryptionService {
public:
    /**
     * @brief Encrypts a string using a main password.
     *
     * @param data The string to be encrypted.
     * @param mainPassword The main password used for encryption.
     * @return The encrypted string.
     */
    static std::string encryptString(const std::string &data, const std::string &mainPassword);
    /**
        * @brief Decrypts an encrypted string using a main password.
        *
        * @param encryptedData The encrypted string to be decrypted.
        * @param mainPassword The main password used for decryption.
        * @return The decrypted string.
        */
    static std::string decryptString(const std::string &encryptedData, const std::string &mainPassword);

};

#endif //PROJECT_ENCRYPTIONSERVICE_H
