#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "..//include/BaseMonitor.h"
#include <windows.h>
#include <vector>
#include <string>
#include "..//include/MonitorCache.h"

class CpuMonitor : public BaseMonitor {
private:
    int activeCores;
    double usagePercentage;
    std::vector<double> history;
    FILETIME prevIdleTime, prevKernelTime, prevUserTime;

    double calculateUsage(FILETIME idle, FILETIME kernel, FILETIME user);
    unsigned long long ft2ull(FILETIME ft);

public:
    CpuMonitor();
    void update() override;
    double getLoad() const;
    void display() const override;
    std::string getLogData() const override { return "CPU_Report"; }
    double getUsagePercentage() const { return usagePercentage; }
    int getActiveCores() const { return activeCores; }
    std::vector<double> getHistory() const { return history; }
    
    void displayCached(const SystemMetrics& data) const;
};

#endif