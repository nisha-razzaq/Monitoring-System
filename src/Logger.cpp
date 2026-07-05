#include "../include/Logger.h"
#include "../include/ConfigManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

static const std::string ACTIVE_LOG = "performance.log";
static const std::string ARCHIVE_PREFIX = "performance_";
static const std::string ARCHIVE_SUFFIX = ".log";

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return std::string(buffer);
}

static std::string getFileSafeTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", local);
    return std::string(buffer);
}

void Logger::rotateLogsIfNeeded() {
    try {
        long long maxBytes = ConfigManager::getMaxLogSizeKB() * 1024LL;
        int maxArchives = ConfigManager::getMaxLogFiles();

        if (maxBytes <= 0 || maxArchives < 1) return;
        if (!fs::exists(ACTIVE_LOG)) return;

        auto currentSize = static_cast<long long>(fs::file_size(ACTIVE_LOG));
        if (currentSize < maxBytes) return;

        // Rotate current log
        std::string archiveName = ARCHIVE_PREFIX + getFileSafeTimestamp() + ARCHIVE_SUFFIX;
        fs::rename(ACTIVE_LOG, archiveName);

        // Recreate active log file
        std::ofstream newLog(ACTIVE_LOG, std::ios::app);
        newLog.close();

        // Collect archives
        std::vector<fs::directory_entry> archives;
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (!entry.is_regular_file()) continue;
            std::string fname = entry.path().filename().string();

            bool isArchive =
                fname.rfind(ARCHIVE_PREFIX, 0) == 0 &&
                fname.size() > ARCHIVE_PREFIX.size() + ARCHIVE_SUFFIX.size() &&
                fname.substr(fname.size() - ARCHIVE_SUFFIX.size()) == ARCHIVE_SUFFIX;

            if (isArchive) archives.push_back(entry);
        }

        // Sort by last write time (newest first)
        std::sort(archives.begin(), archives.end(),
                  [](const fs::directory_entry& a, const fs::directory_entry& b) {
                      return fs::last_write_time(a) > fs::last_write_time(b);
                  });

        // Delete old archives beyond maxArchives
        for (size_t i = static_cast<size_t>(maxArchives); i < archives.size(); ++i) {
            fs::remove(archives[i].path());
        }
    } catch (...) {
        
    }
}

void Logger::logPerformance(const std::string& cpuStatus,
                            const std::string& memStatus,
                            const std::string& diskStatus,
                            const std::string& event) {
    rotateLogsIfNeeded();

    std::ofstream out(ACTIVE_LOG, std::ios::app);
    if (!out.is_open()) {
        std::cout << "Failed to open performance.log\n";
        return;
    }

    out << "[" << getTimestamp() << "] "
        << "CPU=" << cpuStatus << ", "
        << "MEM=" << memStatus << ", "
        << "DISK=" << diskStatus << ", "
        << "EVENT=" << event
        << "\n";
    out.close();
}

void Logger::generateReport() {
    std::ifstream in(ACTIVE_LOG);
    if (!in.is_open()) {
        std::cout << "No active log file found.\n";
        return;
    }

    std::ofstream out("report.csv");
    if (!out.is_open()) {
        std::cout << "Failed to create report.csv\n";
        return;
    }

   out << "==================================================\n";
  out << "                 Log Report                \n";
   out << "==================================================\n";
    out << "Generated at: " << getTimestamp() << "\n\n";

    std::string line;
    int total = 0;
    while (std::getline(in, line)) {
        out << line << "\n";
        total++;
    }

    out << "\nTotal log entries: " << total << "\n";
    in.close();
    out.close();

    std::cout << "Report generated: report.csv\n";
}

void Logger::runStatsSubMenu() {
    std::ifstream in(ACTIVE_LOG);
    if (!in.is_open()) {
        std::cout << "No active log file found.\n";
        return;
    }

    int lines = 0;
    int cpuActive = 0, memActive = 0, diskActive = 0;

    std::string line;
    while (std::getline(in, line)) {
        lines++;
        if (line.find("CPU=Active") != std::string::npos) cpuActive++;
        if (line.find("MEM=Active") != std::string::npos) memActive++;
        if (line.find("DISK=Active") != std::string::npos) diskActive++;
    }
    in.close();

    std::cout << "==================================================\n";
    std::cout<< std::setw(32) << "           Log Statistics        \n";
    std::cout << "==================================================\n";
    std::cout << "Total Entries : " << lines << "\n";
    std::cout << "CPU Active    : " << cpuActive << "\n";
    std::cout << "Memory Active : " << memActive << "\n";
    std::cout << "Disk Active   : " << diskActive << "\n";
    std::cout << "--------------------------------------------------\n";
}
