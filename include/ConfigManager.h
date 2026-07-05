#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

class ConfigManager
{
public:
    static void loadConfig();
    static void runConfigSubMenu();

    static int getRefreshInterval();
    static double getCpuThreshold();
    static double getMemThreshold();
    static double getDiskThreshold();

    // Needed by Logger.cpp
    static long long getMaxLogSizeKB();
    static int getMaxLogFiles();

private:
    static int refreshInterval;
    static double cpuThreshold;
    static double memThreshold;
    static double diskThreshold;

    // Needed by Logger.cpp
    static long long maxLogSizeKB;
    static int maxLogFiles;
};

#endif