#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "BaseMonitor.h"
#include <string>

class DiskMonitor : public BaseMonitor
{
private:
    double totalSpace, usedSpace, freeSpace, usagePercentage;

public:
    DiskMonitor();
    void update() override;
    void display() const override;
    std::string getLogData() const override;
};

#endif