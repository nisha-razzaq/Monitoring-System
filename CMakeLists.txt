cmake_minimum_required(VERSION 3.10)
project(MonitoringSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    
    src/ConfigManager.cpp
    src/CpuMonitor.cpp
    src/DiskMonitor.cpp
    src/Logger.cpp
    src/MemoryMonitor.cpp
    src/ProcessManager.cpp
    src/SystemInfoMonitor.cpp
    src/Utils.cpp
)

add_executable(MonitoringSystem ${SOURCES})

if (WIN32)
    target_link_libraries(MonitoringSystem psapi)
endif()