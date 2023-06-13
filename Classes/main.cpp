#include <iostream>
#include <sstream>
#include "Password.h"
#include "Category.h"
#include "PasswordManager.h"
#include <limits>



void printMenu();

void executeUserChoice(int &choice, std::vector<Password> &passwordsVector, const std::string &path,
                       const std::string &mainPassword,std::vector<Category> &categoryVector);

PasswordManager passwordManager;

int main() {

    int choice;
    std::string mainPassword; //admin123
    std::string path;

    std::cout << "Enter your path: ";
    std::cin >> path;

    std::cout << "Enter your main password: ";
    std::cin >> mainPassword;
    std::cout << "---------------------" << std::endl;
    std::vector<Category> categories = passwordManager.getCategories();

    do {
        std::vector<Password> passwords = passwordManager.readPasswordsFromFile(path, mainPassword);
        printMenu();
        std::cin >> choice;
        executeUserChoice(choice, passwords, path, mainPassword,categories);
        std::cout << "\n";
    } while (choice != 9);

    return 0;
}

void printMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Search passwords\n";
    std::cout << "2. Sort passwords\n";
    std::cout << "3. Add password\n";
    std::cout << "4. Edit password\n";
    std::cout << "5. Delete password(s)\n";
    std::cout << "6. Add category\n";
    std::cout << "7. Delete category\n";
    std::cout << "8. Show all passwords\n";
    std::cout << "9. Exit\n";
    std::cout << "\n";
    std::cout << "Enter your choice: ";
}

void executeUserChoice(int& choice, std::vector<Password> &passwordsVector, const std::string &path,
                       const std::string &mainPassword,std::vector<Category> &categoryVector) {
    switch (choice) {
        case 1: {
            std::string name;
            std::string categoryName;

            std::cout << "Searching passwords...\n";
            std::cout << "Please provide parameters for searching: \n";
            std::cout << "Name:\n";
            std::cin >> name;
            std::cout << "Category name:\n";
            std::cin >> categoryName;

            passwordManager.searchPasswords(name, categoryName);
            break;
        }
        case 2:
            std::cout << "Sorting passwords...\n";
            passwordManager.sortPasswords(SortField::Name, SortField::Category);
            break;
        case 3: {
            std::cout << "Adding a password...\n";

            std::string name;
            std::string password;
            std::string website;
            std::string login;
            std::string categoryName;
            std::string description;
            std::string generatedPasswordOption;

            std::cout << "Name: ";
            std::cin >> name;

            std::cout << "Do you want to generate a password? (yes/no): ";
            std::cin >> generatedPasswordOption;

            if (generatedPasswordOption == "yes") {
                int passwordLength;
                int includeUppercaseInt;
                int includeLowercaseInt;
                int includeSpecialCharsInt;

                // gets the parameters for the generated password
                std::cout << "Password length: \n";
                std::cin >> passwordLength;

                std::cout << "Include uppercase letters? (1 for yes, 0 for no): \n";
                std::cin >> includeUppercaseInt;
                if (includeUppercaseInt != 0 && includeUppercaseInt != 1) {
                    std::cout << "Invalid input. Please enter either 1 or 0 for including uppercase letters.\n";
                    break;
                }

                std::cout << "Include lowercase letters? (1 for yes, 0 for no): \n";
                std::cin >> includeLowercaseInt;
                if (includeLowercaseInt != 0 && includeLowercaseInt != 1) {
                    std::cout << "Invalid input. Please enter either 1 or 0 for including lowercase letters.\n";
                    break;
                }

                std::cout << "Include special characters? (1 for yes, 0 for no): \n";
                std::cin >> includeSpecialCharsInt;
                if (includeSpecialCharsInt != 0 && includeSpecialCharsInt != 1) {
                    std::cout << "Invalid input. Please enter either 1 or 0 for including special characters.\n";
                    break;
                }

                // converting integer values to booleans
                bool includeUppercase = (includeUppercaseInt == 1);
                bool includeLowercase = (includeLowercaseInt == 1);
                bool includeSpecialChars = (includeSpecialCharsInt == 1);

                // generating the password
                std::string generatedPassword = passwordManager.generateRandomPassword(passwordLength, includeUppercase,
                                                                                       includeLowercase,
                                                                                       includeSpecialChars);
                password = generatedPassword;
            } else {
                std::cout << "Password: ";
                std::cin >> password;
            }

            std::cout << "Website: ";
            std::cin >> website;
            std::cout << "Login: ";
            std::cin >> login;

            std::cout << "Now add Category for this password:\n";
            std::cout << "Category Name: ";
            std::cin >> categoryName;
            std::cout << "Category Description: ";
            std::cin >> description;

            Category category(categoryName, description);
            Password password1(name, password, category, website, login);
            passwordManager.addPassword(password1);
            //passwordManager.getCategories().push_back(category);
            passwordManager.savePasswordsToFile(path, mainPassword);

            break;
        }

        case 4: {
            std::cout << "Editing a password...\n";

            std::string name;
            std::cout << "Enter the name of the password to edit: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::string updatedName;
            std::string updatedPassword;
            std::string updatedWebsite;
            std::string updatedLogin;
            std::string updatedCategoryName;
            std::string updatedCategoryDescription;

            std::cout << "Enter the updated details:\n";
            std::cout << "Name: ";
            std::getline(std::cin, updatedName);
            std::cout << "Password: ";
            std::getline(std::cin, updatedPassword);
            std::cout << "Website: ";
            std::getline(std::cin, updatedWebsite);
            std::cout << "Login: ";
            std::getline(std::cin, updatedLogin);
            std::cout << "Category Name: ";
            std::getline(std::cin, updatedCategoryName);
            std::cout << "Category Description: ";
            std::getline(std::cin, updatedCategoryDescription);

            // creating the updated password object
            Category updatedCategory(updatedCategoryName, updatedCategoryDescription);
            Password updatedPasswordObj(updatedName, updatedPassword, updatedCategory, updatedWebsite, updatedLogin);

            // updating the password
            passwordManager.editPassword(name, updatedPasswordObj);
            passwordManager.savePasswordsToFile(path, mainPassword);

            break;
        }

        case 5: {
            std::cout << "Deleting password(s)...\n";

            std::vector<std::string> passwordsToDelete;
            std::string name;

            std::cout << "Enter the name(s) of the password(s) to delete (separate them using spaces):\n";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::istringstream iss(name);
            std::string passwordName;
            while (iss >> passwordName) {
                passwordsToDelete.push_back(passwordName);
            }

            passwordManager.deletePasswords(passwordsToDelete);
            passwordManager.savePasswordsToFile(path, mainPassword);
            break;
        }

        case 6: {
            std::cout << "Adding a category...\n";

            std::string categoryName;
            std::string categoryDescription;

            std::cout << "Category Name: ";
            std::cin >> categoryName;

            std::cout << "Category Description: ";
            std::cin >> categoryDescription;

            Category category(categoryName, categoryDescription);
            passwordManager.addCategory(category);
            categoryVector = passwordManager.getCategories();
            break;
        }

        case 7: {
            std::cout << "Deleting a category...\n";
            std::string categoryName;
            std::cout << "Enter the name of the category to delete: ";
            std::cin >> categoryName;

            passwordManager.deleteCategory(categoryName);
            passwordManager.savePasswordsToFile(path, mainPassword);
            break;
        }

        case 8:
            std::cout << "Displaying passwords...\n";
            for (const auto &password: passwordsVector) {
                password.printDetails();
                std::cout << std::endl;
            }
            break;
        case 9:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
    }
}