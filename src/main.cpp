#include <iostream>
#include <cstdlib>
#include <limits>
#include <thread>
#include <atomic>
#include "../include/MemoryMonitor.h"
#include "../include/CpuMonitor.h"
#include "../include/SystemInfoMonitor.h"
#include "../include/DiskMonitor.h"
#include "../include/ProcessManager.h"
#include "../include/Utils.h"
#include "../include/Logger.h"
#include "../include/ConfigManager.h"
#include "../include/MonitorCache.h"
#include "../include/DataCollector.h"

int main() {
    // 1. Threading Infrastructure
    std::atomic<bool> running(true);
    MetricsCache sharedCache;
    
    // Launch the background monitoring thread to poll hardware
    std::thread worker(runDataCollector, std::ref(sharedCache), std::ref(running));

    ConfigManager::loadConfig();
    int choice;
    
    while (true) {
        clearScreen();
        std::cout << "============================================================\n";
        std::cout << "                TEYZIX SYSTEM RESOURCE MONITOR              \n";
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
                SystemMetrics data = sharedCache.get();
                CpuMonitor cpu;
                cpu.displayCached(data);
                waitForUser();
                break;
            }
           case 3: {
    system("cls");
    SystemMetrics data = sharedCache.get(); 
    
    MemoryMonitor mem(sharedCache); 
    
    mem.displayCached(data); 
    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore(); 
    std::cin.get(); 
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
                ConfigManager::runConfigSubMenu(); 

                waitForUser();
                break;
            }
           
            case 9: {
                // Signal thread to stop and clean up
                running = false;
                if (worker.joinable()) {
                    worker.join(); 
                }
                clearScreen();
                std::cout << "Exiting application...\n";
                std::cout << "============================================================\n";
        std::cout << "                Thanks for using System Monitor              \n";
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
