//
// Created by Lena on 02/06/2023.
//

#ifndef PROJECT_TIMESTAMPSERVICE_H
#define PROJECT_TIMESTAMPSERVICE_H

#include <fstream>
#include <ctime>
#include <string>
#include <iostream>

/**
 * @class TimestampService
 * @brief Provides functionality to save timestamps.
 *
 * The TimestampService class allows for saving timestamps associated with a main password.
 * It provides a method to save the current timestamp to a file, using the specified main password.
 */

class TimestampService {
public:
    /**
     * @brief Saves the current timestamp to a file using the main password.
     *
     * This method saves the current timestamp to a file, ensuring that the timestamp is associated
     * with the specified main password. The file can be later accessed to retrieve the saved timestamp.
     *
     * @param mainPassword The main password used to associate the timestamp.
     */
    void saveTimestamp(const std::string &mainPassword);
};

#endif // PROJECT_TIMESTAMPSERVICE_H
