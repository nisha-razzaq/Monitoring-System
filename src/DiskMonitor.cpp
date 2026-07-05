#include "../include/DiskMonitor.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

DiskMonitor::DiskMonitor() : totalSpace(0), usedSpace(0), freeSpace(0), usagePercentage(0.0) {}

void DiskMonitor::update() {
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
    
    // Get disk space for C: drive
    if (GetDiskFreeSpaceExA("C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
        totalSpace = (double)totalBytes.QuadPart / (1024 * 1024 * 1024); // Convert to GB
        freeSpace = (double)freeBytesAvailable.QuadPart / (1024 * 1024 * 1024);
        usedSpace = totalSpace - freeSpace;
        
        if (totalSpace > 0) {
            usagePercentage = (usedSpace / totalSpace) * 100.0;
        }
    }
}

void DiskMonitor::display() const {
    std::cout << "==================================================\n";
    std::cout<< std::setw(32) << "             Disk Monitoring\n";
std::cout << "==================================================\n";
    
    std::cout << std::setw(20) << "Total Space: " << std::setw(10) << std::fixed << std::setprecision(2) << totalSpace << " GB" << std::endl;
    std::cout << std::setw(19) << "Used Space: "  << std::setw(11) << usedSpace << " GB" << std::endl;
    std::cout << std::setw(19) << "Free Space: "  << std::setw(9) << freeSpace << " GB" << std::endl;
    std::cout << std::setw(16) << "Usage %: "      << std::setw(13) << usagePercentage << " %" << std::endl;

    std::cout << "--------------------------------------------------\n";}

std::string DiskMonitor::getLogData() const {
    return "Disk_Usage:" + std::to_string(usagePercentage) + "%";
    
}