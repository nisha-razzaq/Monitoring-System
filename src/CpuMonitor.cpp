#include "../include/CpuMonitor.h"
#include <iostream>
#include <iomanip>
#include "../include/ConfigManager.h"

CpuMonitor::CpuMonitor() : activeCores(0), usagePercentage(0.0) {
    prevIdleTime = {0, 0}; prevKernelTime = {0, 0}; prevUserTime = {0, 0};
}

unsigned long long CpuMonitor::ft2ull(FILETIME ft) {
    return ((unsigned long long)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
}

double CpuMonitor::calculateUsage(FILETIME idle, FILETIME kernel, FILETIME user) {
    unsigned long long idleDiff = ft2ull(idle) - ft2ull(prevIdleTime);
    unsigned long long kernelDiff = ft2ull(kernel) - ft2ull(prevKernelTime);
    unsigned long long userDiff = ft2ull(user) - ft2ull(prevUserTime);
    unsigned long long totalDiff = kernelDiff + userDiff;

    double usage = (totalDiff == 0) ? 0.0 : (double)(totalDiff - idleDiff) / totalDiff * 100.0;

    prevIdleTime = idle; prevKernelTime = kernel; prevUserTime = user;
    return usage;
}

void CpuMonitor::update() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    activeCores = sysInfo.dwNumberOfProcessors;

    FILETIME idle, kernel, user;
    if (GetSystemTimes(&idle, &kernel, &user)) {
        usagePercentage = calculateUsage(idle, kernel, user);
        history.push_back(usagePercentage);
        if (history.size() > 5) history.erase(history.begin());
    }

    // UPDATED ALERT LOGIC (fixed: use getter instead of private variable)
    if (usagePercentage > ConfigManager::getCpuThreshold()) {
        std::cout << "\n[!!! ALERT !!!] CPU Usage critical: "
                  << usagePercentage << "% (Threshold: "
                  << ConfigManager::getCpuThreshold() << "%)" << std::endl;
    }
}

void CpuMonitor::display() const {
    std::cout << "============================================================\n";
    std::cout << std::setw(35) << "              CPU Statistics\n";
    std::cout << "============================================================\n";

    // 1. Current CPU Usage
    std::cout << std::setw(25) << "Current CPU Usage: " << std::setw(15) << usagePercentage << "%" << std::endl;

    // 2. CPU Load Percentage
    std::cout << std::setw(27) << "CPU Load Percentage: " << std::setw(13) << usagePercentage << "%" << std::endl;

    // 3. Number of Active Cores
    std::cout << std::setw(30) << "Number of Active Cores: " << std::setw(4) << activeCores << std::endl;

    // 4. CPU Usage History
    std::cout << std::setw(25) << "CPU Usage History: ";
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << std::setw(15) << history[i] << "%";
        if (i < history.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------\n";
}