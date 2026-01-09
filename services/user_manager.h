#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <iostream>
#include <string>
#include <map>

class UserManager {
private:
    std::map<std::string, std::string> users; // username -> pin

public:
    UserManager() {
        users["admin"] = "1234";
    }

    bool authenticate(const std::string& user, const std::string& pin) {
        if (users.count(user) && users[user] == pin) {
            std::cout << "[Auth] User " << user << " authenticated successfully.\n";
            return true;
        }
        std::cout << "[Auth] Authentication failed for " << user << ".\n";
        return false;
    }

    void createUser(const std::string& user, const std::string& pin) {
        users[user] = pin;
        std::cout << "[Auth] Profile created for: " << user << "\n";
    }
};

#endif