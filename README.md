# 🖥️ Monitoring System

A C++-based command-line resource monitoring system designed to track key system metrics and provide operational insights.  
It monitors CPU, memory, disk usage, and processes, supports configurable alert thresholds, and includes reporting/statistics features for performance analysis.

---

# 📖 Overview
The Monitoring System is a modular desktop/terminal utility built in **C++** for observing system health in real time.  
Through an interactive menu, users can inspect system information, monitor core resources, manage processes, generate reports, and review statistics.  
The project demonstrates practical system-level programming concepts such as modular architecture, configuration handling, and runtime monitoring workflows.

---

# 🛠️ Technologies
- **C++17** – core language for implementation  
- **CMake** – project build configuration  
- **Windows System APIs / psapi** – process and system-level integration  
- **File Handling** – configuration and logging/report output  
- **Console-based UI** – menu-driven interaction and monitoring displays

---

# ✨ Features
- 📊 **CPU Monitoring** – tracks CPU activity and displays live utilization details  
- 🧠 **Memory Monitoring** – monitors memory usage and reports current status  
- 💽 **Disk Monitoring** – checks disk usage and usage trends  
- ⚙️ **System Information View** – displays overall machine/system details  
- 🧩 **Process Management** – access process-related actions via a dedicated submenu  
- 📝 **Performance Logging** – logs monitoring events and component activity  
- 📑 **Report Generation** – creates reports from collected monitoring data  
- 🔎 **Search & Statistics** – provides log/statistics exploration from the main menu  
- 🔧 **Configuration Management** – runtime configuration submenu for monitor settings  
- 🚨 **Threshold-driven Monitoring** – configurable thresholds for CPU, memory, and disk alerts via `config.txt`

---

# 🔄 Process
1. **Architecture Setup** – designed a modular monitor hierarchy with separate components for each resource type.  
2. **Core Monitoring Modules** – implemented CPU, memory, disk, and system info monitors.  
3. **Process & Utility Layer** – added process management and reusable utility/helper functions.  
4. **Logging and Reporting** – integrated logger functionality for performance records and report generation.  
5. **Configuration Integration** – added config loading and management for refresh intervals and thresholds.  
6. **Interactive CLI Flow** – connected all modules through a structured menu-driven main program.

---

# 📚 What I Learned
- Building a **modular C++ monitoring application** using classes and separated `.h/.cpp` components  
- Using **CMake** for multi-file C++ project organization  
- Integrating system-level monitoring and process-related workflows in a CLI app  
- Managing runtime behavior via **external configuration files**  
- Implementing logging/reporting flows to support observability and diagnostics  
- Improving user interaction through robust input handling and submenu design

---

# 🔧 How It Can Be Improved
- Add **cross-platform support** (Linux/macOS) by abstracting platform-specific APIs  
- Introduce **multi-threaded live monitoring** for smoother real-time updates  
- Export reports in structured formats like **CSV/JSON**  
- Add **graphical dashboards** (Qt/ImGui/web UI) for richer visualization  
- Implement **alert channels** (desktop notification/email/webhook) when thresholds are exceeded  
- Add persistent historical storage for long-term performance trend analysis

---

# 📂 Project Structure
- `BaseMonitor.h` – base abstraction/interface for monitor components  
- `CpuMonitor.h` / `CpuMonitor.cpp` – CPU usage monitoring logic and display  
- `MemoryMonitor.h` / `MemoryMonitor.cpp` – memory monitoring module  
- `DiskMonitor.h` / `DiskMonitor.cpp` – disk usage monitoring module  
- `SystemInfoMonitor.h` / `SystemInfoMonitor.cpp` – system information collection/display  
- `ProcessManager.h` / `ProcessManager.cpp` – process-related monitoring/management actions  
- `Logger.h` / `Logger.cpp` – performance logging, reports, and statistics submenu  
- `ConfigManager.h` / `ConfigManager.cpp` – configuration loading and config submenu operations  
- `Utils.h` / `Utils.cpp` – helper/utility functions (screen clear, input flow helpers, etc.)  
- `main.cpp` – application entry point and interactive menu orchestration  
- `config.txt` – runtime settings (`REFRESH_INTERVAL`, `CPU_THRESHOLD`, `MEM_THRESHOLD`, `DISK_THRESHOLD`)  
- `CMakelists.txt` – CMake build definition for the project executable

---

# ⚙️ Compilation

## Windows (CMD / PowerShell)
```bash
mkdir build
cd build
cmake ..
cmake --build .
dir
.\Task-03.exe
```

## Linux/macOS
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
ls
./Task-03
```
