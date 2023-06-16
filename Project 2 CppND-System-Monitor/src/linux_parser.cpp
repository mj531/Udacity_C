#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

using std::stol;
using std::stoi;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  // std::cerr << "Found " << kernel << "\n" ;
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string memtotal, memfree;
  string line, key, value;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memtotal = value;
        }
        else if (key == "MemFree:") {
          memfree = value;
        }
      }
    }
  }
  return (stof(memtotal) - stof(memfree)) / stof(memtotal); 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime_sec, line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_sec;
  }
   return stol(uptime_sec); 
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return ActiveJiffies() + IdleJiffies(); 
  }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line, value;
  vector<string> vals;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      vals.push_back(value);
    }
  }
  return stol(vals[13]+vals[14]+vals[15]+vals[16]); 
  }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<string> vals = CpuUtilization();
  return stol(vals[CPUStates::kUser_]) + stol(vals[CPUStates::kNice_]) +
         stol(vals[CPUStates::kSystem_]) + stol(vals[CPUStates::kIRQ_]) +
         stol(vals[CPUStates::kSoftIRQ_]) + stol(vals[CPUStates::kSteal_]); 
  }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> vals = CpuUtilization();
  return stol(vals[CPUStates::kIdle_]) + stol(vals[CPUStates::kIOwait_]);  
  }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, cpu, value;
  vector<string> vals;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    while (linestream >> value) {
      vals.push_back(value);
    }
  }
  return vals;
  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {   
  string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "processes") {
            return stoi(value);  
          }
        }
      }
    }
    return 0;
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "procs_running") {
            return stoi(value); 
          }
        }
      }
    }
    return 0;
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, command);
    }
  return command; 
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string key, value, line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "VmRSS:") {
            //since `value` is of type string so to simplify things, 
            //can directly delete the last three characters instead of dividing by 1024(~1000)
            return to_string(stol(value)/1000); 
          }
        }
      }
    }
    return "0";
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string key, value, line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "Uid:") {
            return value; 
          }
        }
      }
    }
    return "0";
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string name, x , value, line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      std::replace(line.begin(), line.end(), ':', ' ');
      while (linestream >> name >> x >> value) {
          if (value == LinuxParser::Uid(pid)) {
            return name; 
          }
        }
      }
    }
    return "NA";
    }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, value;
  vector<string> vals;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      vals.push_back(value);
    }
  }
  return stol(vals[21]) / sysconf(_SC_CLK_TCK);
  }
