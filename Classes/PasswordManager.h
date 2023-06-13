//
// Created by Lena on 26/05/2023.
//

#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <vector>
#include "Password.h"
#include "Category.h"
#include "TimestampService.h"

enum class SortField {
    Name, /// Parameters for sorting
    Category
};
/**
 * @brief The PasswordManager class manages the operations related to password management.
 *
 * The PasswordManager class provides functionality to add, edit, delete, and search passwords,
 * as well as manage password categories and encryption/decryption of passwords.
 */

class PasswordManager {
private:
    std::vector<Password> passwordsVec;    /**< The vector to store the passwords. */
    std::vector<Category> categories;     /**< The vector to store the password categories. */
    TimestampService timestampService;    /**< The TimestampService object to manage timestamps. */

public:
    /**
     * @brief Encrypts a password using the main password.
     * @param password The Password object to be encrypted.
     * @param mainPassword The main password used for encryption.
     * @return The encrypted password as a string.
     */
    std::string encryptPassword(const Password& password, const std::string& mainPassword);
    /**
    * @brief Decrypts an encrypted password using the main password.
    * @param encryptedData The encrypted password data as a string.
    * @param mainPassword The main password used for decryption.
    * @return The decrypted Password object.
    */
    Password decryptPassword(const std::string& encryptedData, const std::string& mainPassword);
    /**
    * @brief Reads passwords from a file, decrypts them, and returns a vector of decrypted passwords.
    * @param path The path to the file containing encrypted passwords.
    * @param mainPassword The main password used for decryption.
    * @return A vector of decrypted Password objects.
    */
    std::vector<Password> readPasswordsFromFile(const std::string& path, const std::string& mainPassword);
    /**
    * @brief Saves the passwords to a file after encrypting them.
    * @param path The path to the file where the encrypted passwords will be saved.
    * @param mainPassword The main password used for encryption.
    */
    void savePasswordsToFile(const std::string& path, const std::string& mainPassword);

    /**
     * @brief Searches for passwords based on name and category.
     * @param name The name to search for in passwords.
     * @param categoryName The category name to search for in passwords.
     */
    void searchPasswords(const std::string& name, const std::string& categoryName) const;
    /**
     * @brief Sorts and prints the passwords based on the specified sort fields.
     * @param field1 The first sort field.
     * @param field2 The second sort field.
     */
    void sortPasswords(SortField field1, SortField field2) const;

    /**
     * @brief Adds a new password to the password vector.
     * @param newPassword The new Password object to be added.
     */
    void addPassword(const Password &newPassword);
    /**
     * @brief Adds an encrypted password to the file.
     * @param path The path to the file where the encrypted password will be added.
     * @param mainPassword The main password used for encryption.
     * @param password The Password object to be encrypted and added to the file.
     */
    void addEncryptedPassword(const std::string& path, const std::string& mainPassword, const Password& password);
    /**
     * @brief Edits an existing password.
     * @param name The name of the password to be edited.
     * @param updatedPassword for setting the new password.
     */
void editPassword(const std::string& name, const Password& updatedPassword);
    /**
      * @brief Deletes a password based on its name.
      * @param name The name of the password to be deleted.
      */
void deletePasswords(const std::vector<std::string>& names);
/**
     * @brief Adds a new category to the categories vector.
     * @param newCategory The new Category object to be added.
     */
void addCategory(const Category& category);
/**
     * @brief Deletes a category based on its name along with passwords with this category.
     * @param name The name of the category to be deleted.
     */
void deleteCategory(const std::string& name);

/**
 * @brief Evaluates the strength of a password.
 *
 * This method evaluates the strength of a given password based on its length and character composition.
 *
 * @param password The password to evaluate.
 * @return A string indicating the strength of the password. Possible values are:
 *         - "Weak" if the password length is less than 4.
 *         - "Moderate" if the password contains either uppercase or lowercase letters, but not both, or if it does not contain any special characters.
 *         - "Strong" if the password contains both uppercase and lowercase letters, as well as at least one special character.
 */
std::string evaluatePasswordStrength(const std::string& password) const;
/**
 * @brief checks if a password has been used before.
 *
 * This method checks if the given password exists in the stored passwords vector.
 *
 * @param password The password to check.
 * @return True if the password has been used before, false otherwise.
 */
bool checkPasswordUsed(const std::string& password) const;
/**
 * @brief Generates a random password with specified properties.
 *
 * This static method generates a random password of a given length, including uppercase letters, lowercase letters, and/or special characters based on the provided flags.
 *
 * @param length The length of the generated password.
 * @param includeUppercase boolean indicating whether to include uppercase letters in the password.
 * @param includeLowercase boolean indicating whether to include lowercase letters in the password.
 * @param includeSpecialChars boolean indicating whether to include special characters in the password.
 * @return The randomly generated password as a string.
 */
static std::string generateRandomPassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars);

/**
 * @brief Retrieves the categories of passwords stored in the password manager.
 *
 * This method returns a vector of Category objects representing the categories of passwords stored in the password manager.
 *
 * @return A vector of Category objects representing the password categories.
 */
std::vector<Category> getCategories() const;
};

#endif // PASSWORDMANAGER_H
