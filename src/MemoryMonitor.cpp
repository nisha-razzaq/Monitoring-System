#include "../include/MemoryMonitor.h"
#include "../include/MonitorCache.h"
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

MemoryMonitor::MemoryMonitor(MetricsCache& c) : cache(c) {
    totalMemory = 0.0;
    usedMemory = 0.0;
    availableMemory = 0.0;
    swapMemory = 0.0;
    memUsagePercentage = 0.0;
}
void MemoryMonitor::display() const {
    std::cout << "Memory Monitor initialized. Use displayCached() to view stats." << std::endl;
}

void MemoryMonitor::update() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        // Convert bytes to MB
        totalMemory = (double)memInfo.ullTotalPhys / (1024 * 1024);
        availableMemory = (double)memInfo.ullAvailPhys / (1024 * 1024);
        usedMemory = totalMemory - availableMemory;
        memUsagePercentage = memInfo.dwMemoryLoad;
    }
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

void MemoryMonitor::displayCached(const SystemMetrics& data) const {
    std::cout << "============================================================\n";
    std::cout << std::setw(30) << "             Memory Statistics\n";
    std::cout << "============================================================\n";
    std::cout << std::setw(9) << "Total: " << std::setw(21) << data.totalMemory << " MB" << std::endl;
    std::cout << std::setw(8) << "Used: " << std::setw(22) << data.usedMemory << " MB" << std::endl;
    std::cout << std::setw(13) << "Available: " << std::setw(16) << data.availableMemory << " MB" << std::endl;
    std::cout << std::setw(20) << "Usage Percentage: " << std::setw(10) << data.memUsagePercentage << " %" << std::endl;
    std::cout << std::setw(15) << "Swap Memory: " << std::setw(13) << data.swapMemory << " MB" << std::endl;

    std::cout << "------------------------------------------------------------\n";}
  std::string MemoryMonitor::getLogData() const {
    // Fetch the latest thread-safe snapshot from the cache
    SystemMetrics data = cache.get(); 
    return "Memory_Usage: " + std::to_string(data.memUsagePercentage) + "%";
}
