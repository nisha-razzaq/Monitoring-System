#include "../include/SystemInfoMonitor.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include<iomanip>

void SystemInfoMonitor::display() const {
    std::cout << "============================================================================\n";
    std::cout << "                    System Information\n";
    std::cout << "============================================================================\n";
   
     // 1. OS
    std::cout << std:: setw(12)<< "OS:"<<std:: setw(35)<<" Windows 10/11" << std::endl;
    // 2. CPU Information
    HKEY hKey;
    char buffer[256];
    DWORD bufferSize = sizeof(buffer);
    
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
            std::cout << std::setw(26)<< "CPU Information: " << std::setw(48)<< buffer << std::endl;
        }
        RegCloseKey(hKey);
    }
    // 3. Memory (Total and Available)
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        std::cout << std :: setw(20)<<"Total RAM: " <<std::setw(19)<< memInfo.ullTotalPhys / 1024 / 1024 << " MB" << std::endl;
        std::cout << std:: setw(24)<<"Available RAM: " << std::setw(14)<<memInfo.ullAvailPhys / 1024 / 1024 << " MB" << std::endl;
    }
 // 4. Disk Capacity
    ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;
    if (GetDiskFreeSpaceExA("C:\\", &freeBytes, &totalBytes, &totalFreeBytes)) {
        std::cout <<std::setw(30)<< "Disk Capacity (C:\\): " <<std::setw(7)<< totalBytes.QuadPart / 1024 / 1024 / 1024 << " GB" << std::endl;
    }
    //5 . Host name
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    if (GetComputerNameA(computerName, &size)) {
        std::cout << std::setw(20)<<"Host Name: " << std::setw(22)<<computerName << std::endl;
    }

    // 2. System Uptime (in days/hours)
    ULONGLONG uptimeSeconds = GetTickCount64() / 1000;
    std::cout << std::setw(24)<<"System Uptime: " << std::setw(11)<<uptimeSeconds / 86400 << "d " 
              << (uptimeSeconds % 86400) / 3600 << "h" << std::endl;
    std::cout << "----------------------------------------------------------------------------\n";

   
    

    

   
}