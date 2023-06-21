#include "processor.h"
#include "linux_parser.h"
#include <cmath>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    auto total = LinuxParser::Jiffies();
    auto active = LinuxParser::ActiveJiffies(); 
    return static_cast<double>(active) / total; 
    }