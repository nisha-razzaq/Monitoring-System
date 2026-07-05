#include "../include/Utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
void waitForUser() {
    std::cout << "\nPress Enter to return to menu...";
    std::cin.sync(); 
    std::cin.get();
}