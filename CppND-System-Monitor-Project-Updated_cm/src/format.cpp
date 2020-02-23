#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 

{
string time;

int hours;
int minutes;
int sec;

minutes = (seconds/60);
hours = (minutes/60);
sec = seconds%(minutes%60;
minutes = minutes - hours*60;

time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
    
return time; 
     
}