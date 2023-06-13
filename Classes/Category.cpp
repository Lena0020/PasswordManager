//
// Created by Lena on 21/05/2023.
//
#include "Category.h"

Category::Category(const std::string &name, const std::string &description)
        : name(name), description(description) {
}

std::string Category::getName() const {
    return name;
}

std::string Category::getDescription() const {
    return description;
}

void Category::setName(const std::string &newName) {
    name = newName;
}

void Category::setDescription(const std::string &newDescription) {
    description = newDescription;
}


