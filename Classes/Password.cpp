//
// Created by Lena on 21/05/2023.
//

#include "Password.h"
#include <iostream>

//constructor
Password::Password(const std::string& name, const std::string& password, const Category& category,
                   const std::string& website, const std::string& login)
        : name(name), password(password), category(category), website(website), login(login) {
}
//getters

std::string Password::getName() const {
    return name;
}

std::string Password::getPassword() const {
    return password;
}

Category Password::getCategory() const {
    return category;
}

std::string Password::getWebsite() const {
    return website;
}

std::string Password::getLogin() const {
    return login;
}

//setters

void Password::setPassword(const std::string &newPassword) {
    password = newPassword;
}

void Password::setCategory(const Category& newCategory) {
    category = newCategory;
}

void Password::setWebsite(const std::string &newWebsite) {
    website = newWebsite;
}

void Password::setLogin(const std::string &newLogin) {
    login = newLogin;
}

//toString
void Password::printDetails() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Category: " << category.getName() << std::endl;
    std::cout << "Website: " << website << std::endl;
    std::cout << "Login: " << login << std::endl;
}
