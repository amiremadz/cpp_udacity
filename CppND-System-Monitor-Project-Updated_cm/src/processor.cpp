#include <string>
#include <iostream>


#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{

    double idle_t, non_idle, total, total_delta, idle_delta, time, time_delta;


    idle_t = LinuxParser::IdleJiffies();
    non_idle = LinuxParser::ActiveJiffies();
    total = LinuxParser::Jiffies();
    time = LinuxParser::UpTime();

    
    total_delta = (total - prev_total);
    idle_delta = (idle_t - prev_idle); 
    time_delta = time - prev_time;


    prev_total = total;
    prev_idle = idle_t;
    prev_time = time;

    return ((total_delta - idle_delta)/total_delta)/(time_delta);

}

