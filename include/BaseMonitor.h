#ifndef BASE_MONITOR_H
#define BASE_MONITOR_H

#include <string>

// Abstract Base Class for all system monitors
class BaseMonitor {
public:
    virtual ~BaseMonitor() = default;

    // Force subclasses to implement data collection and display
    virtual void update() = 0; 
    virtual void display() const = 0;
    virtual std::string getLogData() const = 0;
};

#endif // BASE_MONITOR_H