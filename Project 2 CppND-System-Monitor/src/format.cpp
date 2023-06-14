#include <string>
#include <sstream> 

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hh, mm, ss;
    std::stringstream out;
    
    int time = int(seconds);
    hh = time / 3600;
    time = time % 3600;
    mm = time / 60;
    ss= time % 60;
    out << std::to_string(hh) << ":" << std::to_string(mm)
                              << ":" << std::to_string(ss);
    return out.str();
    }