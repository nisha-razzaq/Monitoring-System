#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include "../include/BaseMonitor.h"
#include "../include/MonitorCache.h"

class MemoryMonitor : public BaseMonitor
{
private:
    MetricsCache& cache;
    double totalMemory;
    double usedMemory;
    double availableMemory;
    double swapMemory;
    double memUsagePercentage;

public:
     MemoryMonitor(MetricsCache& c);
    void update() override;
    void display() const override;
    double getTotalMemory() const { return totalMemory; }
    double getUsedMemory() const { return usedMemory; }
    double getAvailableMemory() const { return availableMemory; }
    double getUsagePercentage() const { return memUsagePercentage; }
    void displayCached(const SystemMetrics& data) const;
   
    std::string getLogData() const override;}; 

#endif