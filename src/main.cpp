#include <iostream>
#include <cstdlib>
#include <memory>
#include<limits>
#include <vector>
#include "../include/MemoryMonitor.h"
#include "../include/CpuMonitor.h"
#include "../include/SystemInfoMonitor.h"
#include "../include/DiskMonitor.h"
#include "../include/ProcessManager.h"
#include "../include/Utils.h"
#include "../include/Logger.h"
#include "../include/ConfigManager.h"

int main() {
    ConfigManager::loadConfig();
    int choice;
    
    while (true) {
        clearScreen();
        clearScreen();

std::cout << "============================================================\n";
std::cout << "              TEYZIX SYSTEM RESOURCE MONITOR\n";
std::cout << "============================================================\n";
std::cout << "  1. System Information\n";
std::cout << "  2. CPU Monitoring\n";
std::cout << "  3. Memory Monitoring\n";
std::cout << "  4. Disk Monitoring\n";
std::cout << "  5. Process Management\n";
std::cout << "  6. Generate Performance Report\n";
std::cout << "  7. Search & Statistics\n";
std::cout << "  8. Configuration Management\n";
std::cout << "  9. Exit\n";
std::cout << "------------------------------------------------------------\n";
std::cout << "Enter your choice : ";
std::cin >> choice;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (choice) {
            case 1: {
                clearScreen();
                SystemInfoMonitor sys;
                sys.display(); 
                waitForUser();
                break;
            }
            case 2: {
                clearScreen();
                CpuMonitor cpu; 
                cpu.update();
                cpu.display();
                Logger::logPerformance("Active", "N/A", "N/A", "None");
                waitForUser();
                break;
            }
            case 3: {
                clearScreen();
                MemoryMonitor mem;
                mem.update(); 
                mem.display();
                Logger::logPerformance("N/A", "Active", "N/A", "None");
                waitForUser();
                break;
            }
            case 4: {
                clearScreen();
                DiskMonitor disk;
                disk.update();
                disk.display();
                Logger::logPerformance("N/A", "N/A", "Active", "None");
                waitForUser();
                break;
            }
            case 5: {
               clearScreen();
                ProcessManager pm;
                pm.update();
                pm.runSubMenu();
                Logger::logPerformance("N/A", "N/A", "N/A", "Process_Manager_Accessed");
                break;
            }
            case 6: {
                clearScreen();
    Logger::generateReport();
    waitForUser();
    break;
}
case 7: {
     clearScreen();
    Logger::runStatsSubMenu();
     waitForUser();
    break;
}
case 8: {         
 clearScreen();
                ConfigManager::runConfigSubMenu(); // Your new config submenu
                waitForUser();
                break;
            }
case 9:
{
    clearScreen();
     std::cout << "Exiting application...\n";
    std::cout << "============================================================\n";
    std::cout << "        Thank you for using System Resource Monitor\n";
    std::cout << "============================================================\n";
   
    return 0;
}
            default:
                std::cout << "Invalid choice. Please try again.\n";
                waitForUser();
                break;
        }
    }
    return 0;
}