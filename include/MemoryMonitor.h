#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "BaseMonitor.h"
#include <string>

class MemoryMonitor : public BaseMonitor {
private:
    unsigned long long totalMemory, usedMemory, availableMemory, swapMemory;
    double usagePercentage;

public:
    MemoryMonitor();
    void update() override;
    void display() const override;
    std::string getLogData() const override;
};

#endif