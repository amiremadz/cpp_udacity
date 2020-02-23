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
    return cpu_; 
}



// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    int pid {};

    Process Larger(0);

    processes_.clear(); // clean out processes from last iteration

    for (int i=0; i < LinuxParser::Pids().size(); i++) //Gather all new processes found in proc
    {
        pid = LinuxParser::Pids()[i];
        processes_.push_back(Process(pid)); 
    }

    for(int i = 0; i < processes_.size() - 1; i++) 
         {                                                //Sort Processes by cpu usage
        for(int j = 0; j < processes_.size() - 1; j ++)
        {
            if(processes_[j].CpuUtilization() < processes_[j+1].CpuUtilization())
                {
                    Larger = processes_[j+1];
                    processes_[j+1] = processes_[j];
                    processes_[j] = Larger;
                }

        }

         }

        return processes_; 
    
    }


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
long System::UpTime() 
{ 
    return LinuxParser::UpTime(); 
}

/*
int main() main function for unit tests

{
    System sys1;
    std::vector<Process> pros = sys1.Processes();

    std::cout << "Processes size: " << pros.size() << "\n";

    
    for (int i= 0; i < 20; i++)
    {
        std::cout << "PID in Process: " << pros[i].Pid() << "\n";
        std::cout << "PID User:" << pros[i].User() << "\n";
        //std::cout << "PID Username: " << pros[i].Username() << "\n";
        std::cout << "PID Processor utilization: " << pros[i].CpuUtilization() << "\n";
        std::cout << "PID Memory Utilization: " << pros[i].Ram() << "\n";
        std::cout << "PID Uptime: " << pros[i].UpTime() << "\n";
        std::cout << "PID Command: " << pros[i].Command() << "\n";

        std::cout << " \n ----------- \n";
    }


}

*/


