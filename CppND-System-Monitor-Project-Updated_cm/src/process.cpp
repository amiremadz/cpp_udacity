#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process (int pid)  //constructor for each process instance with unique PID
{
    PID = pid;
    CpuUtilization(); 
    Command();
    Ram();
    User();
    UpTime();
}

// TODO: Return this process's ID
int Process::Pid() 
{ 
return PID; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
cpu_usage = ((LinuxParser::ActiveJiffies(PID)/ sysconf(_SC_CLK_TCK)) / LinuxParser::UpTime(PID));    
return cpu_usage; 
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
    if (command != " ") return command;

    else 
    {
    command = LinuxParser::Command(PID);
    return command; 
    }
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return LinuxParser::Ram(PID); 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{
    if (user != " ") return user;

    else 
    {
    user = LinuxParser::User(PID);
    return user; 
    }

}

// TODO: Return the aaboveabovege of this process (in seconds)
long int Process::UpTime() 
{ 
    return LinuxParser::UpTime(PID); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }