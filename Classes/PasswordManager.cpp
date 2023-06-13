//
// Created by Lena on 26/05/2023.
//
#include <iostream>
#include "PasswordManager.h"
#include "EncryptionService.h"
#include "TimestampService.h"
#include <fstream>

std::string PasswordManager::encryptPassword(const Password &password, const std::string &mainPassword) {
    std::string encryptedName = EncryptionService::encryptString(password.getName(), mainPassword);
    std::string encryptedText = EncryptionService::encryptString(password.getPassword(), mainPassword);
    std::string encryptedCategoryName = EncryptionService::encryptString(password.getCategory().getName(),
                                                                         mainPassword);
    std::string encryptedCategoryDesc = EncryptionService::encryptString(password.getCategory().getDescription(),
                                                                         mainPassword);
    std::string encryptedWebsite = EncryptionService::encryptString(password.getWebsite(), mainPassword);
    std::string encryptedLogin = EncryptionService::encryptString(password.getLogin(), mainPassword);

    std::string encryptedData = encryptedName + "," + encryptedText + "," + encryptedCategoryName + "," +
                                encryptedCategoryDesc + "," + encryptedWebsite + "," + encryptedLogin;

    return encryptedData;
}

Password PasswordManager::decryptPassword(const std::string &encryptedData, const std::string &mainPassword) {
    std::vector<std::string> encryptedFields;
    std::string encryptedField;

    for (char ch: encryptedData) {
        if (ch == ',') {
            encryptedFields.push_back(encryptedField);
            encryptedField.clear();
        } else {
            encryptedField += ch;
        }
    }

    encryptedFields.push_back(encryptedField);

    std::string decryptedName = EncryptionService::decryptString(encryptedFields[0], mainPassword);
    std::string decryptedText = EncryptionService::decryptString(encryptedFields[1], mainPassword);
    std::string decryptedCategoryName = EncryptionService::decryptString(encryptedFields[2], mainPassword);
    std::string decryptedCategoryDesc = EncryptionService::decryptString(encryptedFields[3], mainPassword);
    std::string decryptedWebsite = EncryptionService::decryptString(encryptedFields[4], mainPassword);
    std::string decryptedLogin = EncryptionService::decryptString(encryptedFields[5], mainPassword);

    Password decryptedPassword(decryptedName, decryptedText, Category(decryptedCategoryName, decryptedCategoryDesc),
                               decryptedWebsite, decryptedLogin);

    return decryptedPassword;
}

void PasswordManager::addEncryptedPassword(const std::string &path, const std::string &mainPassword,
                                           const Password &password) {
    std::string encryptedData = encryptPassword(password, mainPassword);

    std::ofstream file(path, std::ios::app);
    if (!file) {
        std::cout << "Error while opening the file" << std::endl;
        return;
    }

    file << encryptedData << std::endl;
    file.close();
}

std::vector<Password> PasswordManager::readPasswordsFromFile(const std::string &path, const std::string &mainPassword) {
    std::vector<Password> decryptedPasswords;

    std::ifstream file(path);
    if (!file) {
        std::cout << "Error opening the file." << std::endl;
        return decryptedPasswords;
    }

    std::string encryptedData;
    while (std::getline(file, encryptedData)) {
        Password decryptedPassword = decryptPassword(encryptedData, mainPassword);
        decryptedPasswords.push_back(decryptedPassword);
    }

    file.close();
    passwordsVec = decryptedPasswords;
    timestampService.saveTimestamp(mainPassword);
    return decryptedPasswords;
}

void PasswordManager::savePasswordsToFile(const std::string &path, const std::string &mainPassword) {
    std::ofstream file(path);
    if (!file) {
        std::cout << "Error creating/opening the file." << std::endl;
        return;
    }
    timestampService.saveTimestamp(mainPassword);
    for (const Password &password: passwordsVec) {
        std::string encryptedData = encryptPassword(password, mainPassword);
        file << encryptedData << '\n';
    }

    file.close();
}


void PasswordManager::searchPasswords(const std::string &name, const std::string &categoryName) const {
    bool found = false;
    for (const auto &password: passwordsVec) {
        if (password.getName().find(name) != std::string::npos &&
            password.getCategory().getName().find(categoryName) != std::string::npos) {
            password.printDetails();
            std::cout << "---------------------" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No matching passwords found." << std::endl;
    }
}


void PasswordManager::sortPasswords(SortField field1, SortField field2) const {
    std::vector<Password> sortedPasswords = passwordsVec;

    std::sort(sortedPasswords.begin(), sortedPasswords.end(),
              [field1, field2](const Password &password1, const Password &password2) {
                  if (field1 == SortField::Name && field2 == SortField::Category) {
                      if (password1.getName() == password2.getName()) {
                          return password1.getCategory().getName() < password2.getCategory().getName();
                      }
                      return password1.getName() < password2.getName();
                  } else if (field1 == SortField::Category && field2 == SortField::Name) {
                      if (password1.getCategory().getName() == password2.getCategory().getName()) {
                          return password1.getName() < password2.getName();
                      }
                      return password1.getCategory().getName() < password2.getCategory().getName();
                  }
                  // we can add more SortFields and combinations if needed to sort by more things
                  return false; // Default
              });

    for (const auto &password: sortedPasswords) {
        password.printDetails();
        std::cout << "---------------------" << std::endl;
    }
}

void PasswordManager::addPassword(const Password &newPassword) {
    // check how strong is the password
    std::string passwordStrength = evaluatePasswordStrength(newPassword.getPassword());

    // check if the password has been used before
    bool isPasswordUsed = checkPasswordUsed(newPassword.getPassword());

    // informing the user about the password strength and usage history
    std::cout << "Password strength: " << passwordStrength << std::endl;
    if (isPasswordUsed) {
        std::cout << "Warning: This password has been used before.\n";
    }

    // adding the password to the vector
    passwordsVec.push_back(newPassword);

    std::cout << "Password added successfully.\n";
}


void PasswordManager::editPassword(const std::string &name, const Password &updatedPassword) {
    bool passwordFound = false;

    for (auto &password: passwordsVec) {
        if (password.getName() == name) {
            password = updatedPassword;
            passwordFound = true;
            break;
        }
    }

    if (passwordFound) {
        std::cout << "Password updated successfully.\n";
    } else {
        std::cout << "Password not found: " << name << std::endl;
    }
}


void PasswordManager::deletePasswords(const std::vector<std::string> &names) {
    int count = 0;

    for (const auto &name: names) {
        bool found = false;
        for (const auto &password: passwordsVec) {
            if (password.getName() == name) {
                found = true;
                ++count;
            }
        }
        if (!found) {
            std::cout << "Password not found: " << name << std::endl;
        }
    }

    if (count > 0) {
        std::cout << "Are you sure you want to delete " << count << " password(s)?\n";
        std::string confirmation;
        std::cout << "Type 'yes' to confirm: ";
        std::cin >> confirmation;

        if (confirmation == "yes") {
            auto it = passwordsVec.begin();
            while (it != passwordsVec.end()) {
                if (std::find(names.begin(), names.end(), it->getName()) != names.end()) {
                    std::cout << "Deleting password: " << it->getName() << std::endl;
                    it = passwordsVec.erase(it);
                } else {
                    ++it;
                }
            }
            std::cout << count << " password(s) deleted successfully.\n";
        } else {
            std::cout << "Deletion canceled.\n";
        }
    } else {
        std::cout << "No passwords found for deletion.\n";
    }
}

void PasswordManager::addCategory(const Category &category) {
    categories.push_back(category);
    std::cout << "Category added: " << category.getName() << std::endl;
    std::cout << "Total categories: " << categories.size() << std::endl;
}


void PasswordManager::deleteCategory(const std::string &name) {
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        if (it->getName() == name) {
            categories.erase(it);
            break;
        }
    }
    // delete passwordsVec with deleted category
    for (auto it = passwordsVec.begin(); it != passwordsVec.end();) {
        if (it->getCategory().getName() == name) {
            it = passwordsVec.erase(it);
        } else {
            ++it;
        }
    }
    std::cout << "Category along with the passwords assigned to this category - deleted \n";
}

bool PasswordManager::checkPasswordUsed(const std::string &password) const {
    // checks if the password exists in the passwordsVec vector
    for (const auto &storedPassword: passwordsVec) {
        if (storedPassword.getPassword() == password) {
            return true; // password has been used before
        }
    }
    return false; // password has not been used before
}

std::string PasswordManager::evaluatePasswordStrength(const std::string &password) const {

    if (password.length() < 4) {
        return "Weak";
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasSpecialChar = false;

    for (char c: password) {
        if (std::isupper(c)) {
            hasUppercase = true;
        } else if (std::islower(c)) {
            hasLowercase = true;
        } else if (!std::isalnum(c)) {
            hasSpecialChar = true;
        }
    }

    if (hasUppercase && hasLowercase && hasSpecialChar) {
        return "Strong";
    }

    return "Moderate";
}

std::string PasswordManager::generateRandomPassword(int length, bool includeUppercase, bool includeLowercase,
                                                    bool includeSpecialChars) {
    std::string password;
    std::string characters; // basically characters to choose from

    if (includeUppercase) {
        characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    if (includeLowercase) {
        characters += "abcdefghijklmnopqrstuvwxyz";
    }

    if (includeSpecialChars) {
        characters += "!@#$%^&*";
    }

    // generates random password
    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % characters.length();
        password += characters[randomIndex];
    }

    return password;
}

std::vector<Category> PasswordManager::getCategories() const {
    return categories;
}
