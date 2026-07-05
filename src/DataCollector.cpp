#include "../include/DataCollector.h"
#include "../include/CpuMonitor.h"
#include "../include/MemoryMonitor.h"
#include <thread>
#include <chrono>

void runDataCollector(MetricsCache& cache, std::atomic<bool>& running) {
    
    CpuMonitor cpu;
    MemoryMonitor mem(cache);

    while (running) {

        cpu.update();
        mem.update();
        SystemMetrics m;
        m.cpuUsage = cpu.getUsagePercentage(); 
        m.cpuLoad = cpu.getLoad();
        m.activeCores = cpu.getActiveCores(); 
        m.history = cpu.getHistory();
        m.memUsage = mem.getUsagePercentage();
        m.totalMemory = mem.getTotalMemory(); 
        m.usedMemory = mem.getUsedMemory();
        m.availableMemory = mem.getAvailableMemory();
        m.memUsagePercentage = mem.getUsagePercentage();
        cache.update(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}