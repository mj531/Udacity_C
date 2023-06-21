#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stol;

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    //subtract the process start time from the system uptime
    auto uptime = LinuxParser::UpTime() - LinuxParser::UpTime(Pid());;
    auto active = LinuxParser::ActiveJiffies(Pid());
    return float(active) / float(uptime); 
    }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
// UpTime() returns time the process started after system 
// starttime  %llu
//     The time the process started after system boot.  In
//     kernels before Linux 2.6, this value was expressed
//     in jiffies.  Since Linux 2.6, the value is
//     expressed in clock ticks (divide by
//     sysconf(_SC_CLK_TCK)).
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
bool Process::operator<(Process const& a) const { 
    // return true;
    return CpuUtilization()<a.CpuUtilization();
    // return stol(Ram())<stol(a.Ram()); 
    }