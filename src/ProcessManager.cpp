#include "../include/ProcessManager.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "../include/Utils.h"

void ProcessManager::refreshProcessList() {
    processes.clear();
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnap, &pe32)) {
        do {
            ProcessInfo pi;
            pi.pid = pe32.th32ProcessID;
            pi.name = std::string(pe32.szExeFile);
            pi.memoryUsage = 0; 
            pi.cpuTime = 0;

            HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pi.pid);
            if (hProc) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc))) 
                    pi.memoryUsage = pmc.WorkingSetSize / 1024;
                
                FILETIME create, exit, kernel, user;
                if (GetProcessTimes(hProc, &create, &exit, &kernel, &user)) 
                    pi.cpuTime = *(ULONGLONG*)&kernel + *(ULONGLONG*)&user;
                
                CloseHandle(hProc);
            }
            processes.push_back(pi);
        } while (Process32Next(hSnap, &pe32));
    }
    CloseHandle(hSnap);
}

void ProcessManager::update() { 
    refreshProcessList(); 
}

void ProcessManager::display() const {
    std::cout << std::left << std::setw(8) << "PID" << std::setw(65) << "Name" 
              << std::setw(15) << "Mem(KB)" << "CPU Time\n";
    for (const auto& p : processes) {
        std::cout << std::left << std::setw(8) << p.pid << std::setw(65) << p.name 
                  << std::setw(15) << p.memoryUsage << p.cpuTime << "\n";
    }
}

void ProcessManager::runSubMenu() {
    bool inSubMenu = true;
    int ch;
    std::string s;
    DWORD pid;

    while (inSubMenu) {
        clearScreen(); // Using your Utils function
        
        refreshProcessList();
        std::cout << "============================================================\n";
        std::cout << "              Process Manager\n";
        std::cout << "============================================================\n";
      
        std::cout << "1. Sort Memory" << std::endl;
        std::cout << "2. Sort CPU" << std::endl;
        std::cout << "3. Search" << std::endl;
        std::cout << "4. Terminate" << std::endl;
        std::cout << "5. Back\n";
        std::cout << "------------------------------------------------------------\n";
        std::cout << " Choice: ";
        
        if (!(std::cin >> ch)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer here

        switch (ch) {
            case 1:
                std::sort(processes.begin(), processes.end(), [](auto& a, auto& b) { return a.memoryUsage > b.memoryUsage; });
                display();
                waitForUser();
                break;
            case 2:
                std::sort(processes.begin(), processes.end(), [](auto& a, auto& b) { return a.cpuTime > b.cpuTime; });
                display();
                waitForUser();
                break;
            case 3:
                std::cout << "Search name: ";
                std::cin >> s;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                for (const auto& p : processes) {
                    if (p.name.find(s) != std::string::npos) 
                        std::cout << p.pid << " : " << p.name << "\n";
                }
                waitForUser();
                break;
            case 4:
                std::cout << "Enter PID: ";
                std::cin >> pid;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                terminateProcess(pid);
                waitForUser();
                break;
            case 5:
                inSubMenu = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
                waitForUser();
        }
    }
}
void ProcessManager::terminateProcess(DWORD pid) {
    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (h && TerminateProcess(h, 0)) std::cout << "Terminated PID: " << pid << "\n";
    else std::cout << "Access Denied.\n";
    if (h) CloseHandle(h);
}

std::string ProcessManager::getLogData() const {
    return "Process_Manager_Active";
}