#include "../include/CpuMonitor.h"
#include <iostream>
#include <iomanip>
#include "../include/ConfigManager.h"
#include <pdh.h>
#pragma comment(lib, "pdh.lib")

CpuMonitor::CpuMonitor() : activeCores(0), usagePercentage(0.0) {
    prevIdleTime = {0, 0}; prevKernelTime = {0, 0}; prevUserTime = {0, 0};
}


void CpuMonitor::display() const {
    std::cout << "CpuMonitor: Use displayCached() with system metrics." << std::endl;
}

double CpuMonitor::getLoad() const {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuCounter;
    PdhOpenQuery(NULL, 0, &cpuQuery);
    PdhAddCounter(cpuQuery, "\\System\\Processor Queue Length", 0, &cpuCounter);
    PdhCollectQueryData(cpuQuery);
    
    PDH_FMT_COUNTERVALUE counterVal;
    PdhGetFormattedCounterValue(cpuCounter, PDH_FMT_DOUBLE, NULL, &counterVal);
    PdhCloseQuery(cpuQuery);
    
    return counterVal.doubleValue;
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

    if (usagePercentage > ConfigManager::getCpuThreshold()) {
        std::cout << "\n[!!! ALERT !!!] CPU Usage critical: "
                  << usagePercentage << "% (Threshold: "
                  << ConfigManager::getCpuThreshold() << "%)" << std::endl;
    }
}

// 3. Your specific UI logic using cached data
void CpuMonitor::displayCached(const SystemMetrics& data) const {
    std::cout << "============================================================\n";
    std::cout << std::setw(35) << "              CPU Statistics\n";
    std::cout << "============================================================\n";

    std::cout << std::setw(25) << "Current CPU Usage: " << std::setw(21) << data.cpuUsage << "%" << std::endl;
    std::cout << std::setw(24) << "CPU Load(Queue) : " << std::setw(13) << data.cpuLoad << std::endl;
    std::cout << std::setw(30) << "Number of Active Cores: " << std::setw(10) << data.activeCores << std::endl;

    std::cout << std::setw(25) << "CPU Usage History: ";
    for (size_t i = 0; i < data.history.size(); ++i) {
        std::cout << std::setw(21) << data.history[i] << "%";
        if (i < data.history.size() - 1) std::cout << "\n"<< std::setw(25) << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------\n";
}