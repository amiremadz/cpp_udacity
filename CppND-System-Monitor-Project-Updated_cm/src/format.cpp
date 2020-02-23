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
long minutes;
int sec;



hours = seconds/3600;
minutes = (seconds - (hours*3600))/60;
sec = seconds - (minutes*60) - (hours*3600);

time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
    
return time; 
     
}