#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include "BaseMonitor.h"
#include <windows.h>
#include <vector>

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
    void display() const override;
    std::string getLogData() const override { return "CPU_Report"; }
};

#endif