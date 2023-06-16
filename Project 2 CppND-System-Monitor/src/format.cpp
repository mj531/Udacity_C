#include <string>
#include <sstream> 

#include <iomanip>
#include "format.h"

// #include <chrono> //alternative solution
using std::string;

#define sec_in_min 60
#define min_in_hr 60
#define sec_in_hr sec_in_min * min_in_hr

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hh, mm, ss;
    std::stringstream out;
    
    hh = seconds / sec_in_hr;
    seconds = seconds % sec_in_hr;
    mm = seconds / sec_in_min;
    ss = seconds % sec_in_min;
    // out << std::to_string(hh) << ":" << std::to_string(mm)
    //                           << ":" << std::to_string(ss);
    //
    out << std::setw(2) << std::setfill('0') << hh << ":" 
     << std::setw(2) << std::setfill('0') << mm << ":"
     << std::setw(2) << std::setfill('0') << ss;
    return out.str();

    // //Alternative Implementation:
    // std::chrono::seconds ss{seconds};
    // // return std::chrono::format("%T", seconds); //in C++20 
    // std::chrono::hours hh = std::chrono::duration_cast<std::chrono::hours>(ss);
    // ss -= std::chrono::duration_cast<std::chrono::seconds>(hh);
    // std::chrono::minutes mm = std::chrono::duration_cast<std::chrono::minutes>(ss);
    // ss -= std::chrono::duration_cast<std::chrono::seconds>(mm);

    // std::stringstream out{};
    // out << std::setw(2) << std::setfill('0') << hh.count() //HH
    //    << std::setw(1) << ":"
    //    << std::setw(2) << std::setfill('0') << mm.count() //MM
    //    << std::setw(1) << ":"
    //    << std::setw(2) << std::setfill('0') << ss.count(); //SS
    // return out.str();
    }