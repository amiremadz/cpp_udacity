#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include <iostream>

//#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


// TODO: Return the system's CPU
Processor& System::Cpu() 
{
    cpu_util = cpu_.Utilization();
    return cpu_; 
}

float System::GetCpu()
{
    Cpu();
    return cpu_util;
}


/*
// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    for (int i : LinuxParser::Pids()) 
    {
        Process LinuxParser::Pids()[i];
        processes_.push_back(LinuxParser::Pids()[i]); 
    }
    
    return processes_; }

    */

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() 
{ 
    return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() 
{ 
    return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() 
{ 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() 
{ 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() 
{ 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() 
{ 
    return LinuxParser::UpTime(); 
}

int main() 
{
    System sys1;
    std::cout << "Kernel: " << sys1.Kernel() << "\n";
    std::cout << "Utilization: " << sys1.GetCpu() << "\n";

}