//
// Created by Lena on 27/05/2023.
//

#include "EncryptionService.h"
#include <cctype>

std::string EncryptionService::encryptString(const std::string& data, const std::string& mainPassword) {
    std::string encryptedData;
    int passwordLength = mainPassword.length();
    int countDigitsInPassword = 0;

    for (int i = 0; i < passwordLength; i++) {
        if (std::isdigit(mainPassword[i])) {
            countDigitsInPassword++;
        }
    }

    for (int i = 0; i < data.length(); i++) {
        char currentChar = data[i];
        char passwordChar = mainPassword[i % passwordLength];

        currentChar = currentChar + passwordChar + countDigitsInPassword;

        encryptedData += currentChar;
    }

    return encryptedData;
}

std::string EncryptionService::decryptString(const std::string& encryptedData, const std::string& mainPassword) {
    std::string decryptedData;
    int passwordLength = mainPassword.length();
    int countDigitsInPassword = 0;

    for (int i = 0; i < passwordLength; i++) {
        if (std::isdigit(mainPassword[i])) {
            countDigitsInPassword++;
        }
    }

    for (int i = 0; i < encryptedData.length(); i++) {
        char currentChar = encryptedData[i];
        char passwordChar = mainPassword[i % passwordLength];

        currentChar = currentChar - passwordChar - countDigitsInPassword;

        decryptedData += currentChar;
    }

    return decryptedData;
}



