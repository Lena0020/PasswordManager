//
// Created by Lena on 21/05/2023.
//

#ifndef PROJECT_PASSWORD_H
#define PROJECT_PASSWORD_H
#include <string>
#include "Category.h"
/**
 * @class Password
 * @brief Represents a password entry with associated information.
 *
 * The Password class encapsulates the details of a password, including its name,
 * value, category, website, and login information. It provides methods to access
 * and modify these attributes, as well as a method to print the password details.
 */

class Password {
private:
    std::string name; ///< The name of the password.
    std::string password; ///< The password value.
    Category category; ///< The category to which the password belongs.
    std::string website; ///< The website associated with the password.
    std::string login; ///< The login information associated with the password.

public:
    /**
     * @brief Constructs a Password object with the specified attributes.
     *
     * @param name The name of the password.
     * @param password The password value.
     * @param category The category to which the password belongs.
     * @param website The website associated with the password (optional, default: "").
     * @param login The login information associated with the password (optional, default: "").
     */
    Password(const std::string& name, const std::string& password, const  Category& category,
             const std::string& website = "", const std::string& login = "");

    //getters

    std::string getName() const;
    std::string getPassword() const;
    Category getCategory() const;
    std::string getWebsite() const;
    std::string getLogin() const;

    //setters

    void setPassword(const std::string& newPassword);
    void setCategory(const Category& newCategory);
    void setWebsite(const std::string& newWebsite);
    void setLogin(const std::string& newLogin);

/**
     * @brief Prints the details of the password.
     *
     * This method prints the name, password value, category, website, and login information
     * associated with the password to the standard output.
     */
    void printDetails() const;
};

#endif //PROJECT_PASSWORD_H
