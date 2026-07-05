#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include "../include/MonitorCache.h"
#include "../include/CpuMonitor.h"
#include "../include/MemoryMonitor.h"
#include <atomic>

// This function will be executed by the background thread
void runDataCollector(MetricsCache& cache, std::atomic<bool>& running);

#endif