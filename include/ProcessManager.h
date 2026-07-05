#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "BaseMonitor.h"
#include <windows.h>
#include <vector>
#include <string>

struct ProcessInfo {
    DWORD pid;
    std::string name;
    SIZE_T memoryUsage; // KB
    ULONGLONG cpuTime;  // Cumulative time
};

class ProcessManager : public BaseMonitor {
private:
    std::vector<ProcessInfo> processes;
    void refreshProcessList();

public:
    void update() override;
    void display() const override;
    void runSubMenu();
    void terminateProcess(DWORD pid);
    std::string getLogData() const override; // Added to satisfy BaseMonitor
};
#endif