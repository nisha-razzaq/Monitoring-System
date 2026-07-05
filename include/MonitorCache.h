#pragma once
#include <mutex>
#include <vector>

struct SystemMetrics {
    double cpuUsage = 0.0;
    double cpuLoad = 0.0;
    double memUsage = 0.0;
    int activeCores = 0; 
    std::vector<double> history; 
    double totalMemory = 0.0;
    double usedMemory = 0.0;
    double availableMemory = 0.0;
    double memUsagePercentage = 0.0;
    double swapMemory = 0.0;};

class MetricsCache {
private:
    SystemMetrics data;
    std::mutex mtx;
public:
   void update(const SystemMetrics& newData) { 
        std::lock_guard<std::mutex> lock(mtx);
        data = newData;
    }
    SystemMetrics get() {
        std::lock_guard<std::mutex> lock(mtx);
        return data;
    }
};