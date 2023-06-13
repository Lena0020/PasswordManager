//
// Created by Lena on 21/05/2023.
//

#ifndef PROJECT_CATEGORY_H
#define PROJECT_CATEGORY_H
#include <string>
/**
 * @class Category
 * @brief Represents a category for password entries.
 *
 * The Category class represents a category to which a password can belong.
 * It encapsulates the name and description of the category and provides
 * methods to access and modify these attributes.
 */
class Category {
private:
    std::string name; ///< The name of the category.
    std::string description; ///< The description of the category.

public:
    /**
     * @brief Constructs a Category object with the specified attributes.
     *
     * @param name The name of the category.
     * @param description The description of the category.
     */
    Category(const std::string& name, const std::string& description);

    // getters

    std::string getName() const;
    std::string getDescription() const;

    //setters

    void setName(const std::string& newName);
    void setDescription(const std::string& newDescription);
};

#endif //PROJECT_CATEGORY_H
