#include <string>
//#include <sstream>
//#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long h = seconds/3600;
    int m = (seconds%3600)/60;
    int s = seconds%60;

    string hh = (h>9)? std::to_string(h) : "0" + std::to_string(h); //if there are more than 99 hours, still works
    string mm = (m>9)? std::to_string(m) : "0" + std::to_string(m);
    string ss = (s>9)? std::to_string(s) : "0" + std::to_string(s);
    
    return hh+":"+mm+":"+ss;
}