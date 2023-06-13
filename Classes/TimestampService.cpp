//
// Created by Lena on 02/06/2023.
//
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include "EncryptionService.h"
#include "TimestampService.h"

void TimestampService::saveTimestamp(const std::string& mainPassword) {
    std::ofstream timestampFile("C:\\Users\\Lena\\CLionProjects\\Project\\EncryptedTimestamp.txt");
    if (timestampFile) {
        std::time_t seconds = std::time(nullptr);
        auto localised = std::localtime(&seconds);
        auto timestamp = std::asctime(localised);
        if (timestamp) {
            // encrypting the timestamp using the main password
            std::string encryptedTimestamp = EncryptionService::encryptString(timestamp, mainPassword);

            timestampFile << encryptedTimestamp << '\n';
            timestampFile.close();
        } else {
            std::cerr << "Error: Failed to convert timestamp.\n";
        }
    } else {
        std::cerr << "Error: Failed to open timestamps file for writing.\n";
    }
}
