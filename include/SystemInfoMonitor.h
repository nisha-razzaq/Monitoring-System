#ifndef SYSTEM_INFO_MONITOR_H
#define SYSTEM_INFO_MONITOR_H

#include "BaseMonitor.h"
#include <windows.h>
#include <string>

class SystemInfoMonitor : public BaseMonitor {
public:
    void update() override {} // These are mostly static
    void display() const override;
    std::string getLogData() const override { return "System_Info_Reported"; }
};

#endif