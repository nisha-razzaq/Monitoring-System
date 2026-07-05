#include "../include/ConfigManager.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "../include/Utils.h"

// Static member definitions
int ConfigManager::refreshInterval = 2;
double ConfigManager::cpuThreshold = 80.0;
double ConfigManager::memThreshold = 90.0;
double ConfigManager::diskThreshold = 95.0;

// Required by Logger.cpp
long long ConfigManager::maxLogSizeKB = 512;
int ConfigManager::maxLogFiles = 5;

void ConfigManager::loadConfig() {
    std::ifstream file("config.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.find("REFRESH_INTERVAL=") == 0) {
                refreshInterval = std::stoi(line.substr(17));
            } else if (line.find("CPU_THRESHOLD=") == 0) {
                cpuThreshold = std::stod(line.substr(14));
            } else if (line.find("MEM_THRESHOLD=") == 0) {
                memThreshold = std::stod(line.substr(14));
            } else if (line.find("DISK_THRESHOLD=") == 0) {
                diskThreshold = std::stod(line.substr(15));
            } else if (line.find("MAX_LOG_SIZE_KB=") == 0) {
                maxLogSizeKB = std::stoll(line.substr(16));
            } else if (line.find("MAX_LOG_FILES=") == 0) {
                maxLogFiles = std::stoi(line.substr(14));
            }
        }
    }
}

int ConfigManager::getRefreshInterval() { loadConfig(); return refreshInterval; }
double ConfigManager::getCpuThreshold() { loadConfig(); return cpuThreshold; }
double ConfigManager::getMemThreshold() { loadConfig(); return memThreshold; }
double ConfigManager::getDiskThreshold() { loadConfig(); return diskThreshold; }
long long ConfigManager::getMaxLogSizeKB() { loadConfig(); return maxLogSizeKB; }
int ConfigManager::getMaxLogFiles() { loadConfig(); return maxLogFiles; }

void ConfigManager::runConfigSubMenu() {
    int choice = 0;

    while (true) {
        clearScreen();
        std::cout << "============================================================\n";
        std::cout << "               Configuration Management Menu:\n";
        std::cout << "============================================================\n";
       
        std::cout << "1. View current configuration\n";
        std::cout << "2. Set refresh interval\n";
        std::cout << "3. Set CPU threshold\n";
        std::cout << "4. Set Memory threshold\n";
        std::cout << "5. Set Disk threshold\n";
        std::cout << "6. Back\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 6) return;

        clearScreen();

        switch (choice) {
            case 1:
                std::cout << "REFRESH_INTERVAL = " << refreshInterval << "\n";
                std::cout << "CPU_THRESHOLD   = " << cpuThreshold << "\n";
                std::cout << "MEM_THRESHOLD   = " << memThreshold << "\n";
                std::cout << "DISK_THRESHOLD  = " << diskThreshold << "\n";
                waitForUser();
                break;

            case 2:
                std::cout << "Enter new REFRESH_INTERVAL: ";
                std::cin >> refreshInterval;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Updated.\n";
                waitForUser();
                break;

            case 3:
                std::cout << "Enter new CPU_THRESHOLD: ";
                std::cin >> cpuThreshold;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Updated.\n";
                waitForUser();
                break;

            case 4:
                std::cout << "Enter new MEM_THRESHOLD: ";
                std::cin >> memThreshold;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Updated.\n";
                waitForUser();
                break;

            case 5:
                std::cout << "Enter new DISK_THRESHOLD: ";
                std::cin >> diskThreshold;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Updated.\n";
                waitForUser();
                break;

            default:
                std::cout << "Invalid choice.\n";
                waitForUser();
                break;
        }
    }}