#include "../include/MemoryMonitor.h"
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

MemoryMonitor::MemoryMonitor() : totalMemory(0), usedMemory(0), availableMemory(0), swapMemory(0), usagePercentage(0.0) {}

void MemoryMonitor::update() {
    // 1. Physical Memory
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        totalMemory = memInfo.ullTotalPhys / 1024 / 1024;
        availableMemory = memInfo.ullAvailPhys / 1024 / 1024;
        usedMemory = totalMemory - availableMemory;
        usagePercentage = (double)usedMemory / totalMemory * 100.0;
    }

    // 2. Swap Memory (Page File)
    PERFORMANCE_INFORMATION perfInfo;
    if (GetPerformanceInfo(&perfInfo, sizeof(perfInfo))) {
        unsigned long long totalCommitted = (unsigned long long)perfInfo.CommitTotal * perfInfo.PageSize;
        unsigned long long totalPhysical = (unsigned long long)perfInfo.PhysicalTotal * perfInfo.PageSize;
        
        if (totalCommitted > totalPhysical) {
            swapMemory = (totalCommitted - totalPhysical) / 1024 / 1024;
        } else {
            swapMemory = 0;
        }
    }
}

void MemoryMonitor::display() const {
    std::cout << "============================================================\n";
    std::cout << std::setw(30) << "             Memory Statistics\n";
    std::cout << "============================================================\n";
    std::cout << std::setw(9) << "Total: " << std::setw(21) << totalMemory << " MB" << std::endl;
    std::cout << std::setw(8) << "Used: " << std::setw(22) << usedMemory << " MB" << std::endl;
    std::cout << std::setw(13) << "Available: " << std::setw(16) << availableMemory << " MB" << std::endl;
    std::cout << std::setw(20) << "Usage Percentage: " << std::setw(10) << usagePercentage << " %" << std::endl;
    std::cout << std::setw(15) << "Swap Memory: " << std::setw(13) << swapMemory << " MB" << std::endl;

    std::cout << "------------------------------------------------------------\n";}

std::string MemoryMonitor::getLogData() const {
    return "Memory_Usage:" + std::to_string(usagePercentage) + "%";
}