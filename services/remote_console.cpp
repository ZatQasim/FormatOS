#ifndef REMOTE_CONSOLE_H
#define REMOTE_CONSOLE_H

#include <iostream>
#include <string>

void initRemoteConsole() {
    std::cout << "[Remote Console] Remote access service started on port 2222.\n";
}

void logToConsole(const std::string& msg) {
    std::cout << "[Remote Console Log] " << msg << "\n";
}

#endif