#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void logPerformance(const std::string& cpuStatus,
                               const std::string& memStatus,
                               const std::string& diskStatus,
                               const std::string& event);

    static void generateReport();
    static void runStatsSubMenu();

private:
    static void rotateLogsIfNeeded();
    static std::string getTimestamp();
};

#endif