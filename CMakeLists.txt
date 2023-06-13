cmake_minimum_required(VERSION 3.24)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project Classes/main.cpp Classes/Password.cpp Classes/Password.h Classes/Category.cpp Classes/Category.h Classes/PasswordManager.cpp Classes/PasswordManager.h Classes/EncryptionService.cpp Classes/EncryptionService.h Classes/TimestampService.cpp Classes/TimestampService.h)
