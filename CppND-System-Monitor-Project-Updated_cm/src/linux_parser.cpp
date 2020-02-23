#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() 
{
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
string LinuxParser::Kernel() 
{
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() 
{
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
  string line;
  string key;
  double value;
  double mem_total;
  double mem_free;
  double mem_avail;
  double buffers;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "MemTotal") mem_total = value;
          if (key == "MemFree") mem_free = value;
          if (key == "MemAvailable") mem_avail = value;
          if (key == "Buffers") buffers = value;
    }
   }
   }
   return ((mem_total - mem_free)/mem_total); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  long active, idle {};
  int excess1, excess2 {};
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), '.', ' ');
    std::istringstream linestream(line);
    linestream >> active >> excess1 >> idle >> excess2;

  }
  return active + idle;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{
  long sum {};

  for (int i= 0; i < LinuxParser::CpuUtilization().size(); i ++)
  {
    sum += stoi(LinuxParser::CpuUtilization()[i]);
  }
  return sum; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int PID)
 {  
  long CpuData {};
  string line, cpu;
  int counter = 0;
  std::ifstream stream(kProcDirectory + to_string(PID) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::stringstream linestream(line);
    while (linestream >> cpu)
    {
      if (counter > 12 && counter < 18)
      {
        CpuData += (stol(cpu));
      }
      if (counter == 22)
      {
        CpuData += (stol(cpu));;
      }

      counter ++;
    }
  }
  return CpuData;
   }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
 { 
   long sum{};
    for (int i= 0; i < LinuxParser::CpuUtilization().size(); i ++)
    {
      if (i != 3 && i != 4)
      {
        sum += stoi(LinuxParser::CpuUtilization()[i]);
      } 
    }
   return sum; 
  }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{ 
  int idle {3};
  int iowait {4};
  return stoi(LinuxParser::CpuUtilization()[idle]) + stoi(LinuxParser::CpuUtilization()[iowait]); 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
  vector<string> CpuData {};
  string line, cpu;
  int counter = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::stringstream linestream(line);
    while (linestream >> cpu)
    {
      if (cpu != "cpu" && counter <= 8)
      {
      CpuData.push_back(cpu);
      }
      counter ++;
    }
  }
  return CpuData;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  string line;
  string k;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> k >> value) {
        if (k == "processes") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int PID) 
{ 
  string pid = to_string(PID);
  string line;
  string key;
  string value;
  string command;

  std::ifstream filestream(kProcDirectory + pid + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> value) {
          command += value;
          command += " ";
    }
   }
   }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int PID)
 {
  string value;
  string line;
  string key;
  string ram;

  std::ifstream filestream(kProcDirectory + to_string(PID) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "VmSize") ram = value;
    }
   }
   }
   return ram; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int PID) 
{ 
  string pid = to_string(PID);
  string line;
  string key;
  string value;
  string uid;

  std::ifstream filestream(kProcDirectory + pid + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
          if (key == "Uid") uid = value;
    }
   }
   }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int PID) 
{
  string line;
  string uid = LinuxParser::Uid(PID);
  string value;
  string key;
  string user;
  string domain;

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> domain >> value) { 
          if (value == uid) user = key;
          else break;
      }
    }
   }
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int PID) 
{ 
  long CpuData {};
  string line, cpu;
  int counter = 0;
  std::ifstream stream(kProcDirectory + to_string(PID) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::stringstream linestream(line);
    while (linestream >> cpu)
    {
      if (counter == 23)
      {
        CpuData = (stol(cpu));;
      }

      counter ++;
    }
  }
  return UpTime() - CpuData/sysconf(_SC_CLK_TCK);

  
}


/*
int main ()

{

  std::cout << "Operating System: " << LinuxParser::OperatingSystem() << "\n";
  std::cout << "Kernel: " << LinuxParser::Kernel() << "\n";

  std::cout << "Mem Utilization: " << LinuxParser::MemoryUtilization() << "\n";

  
  std::cout <<"PIDs: \n";

  for (int i = 0; i < LinuxParser::Pids().size(); i++ )
  {
    std::cout << LinuxParser::Pids()[i] << " ";

    if (i%10 == 0)
    {
      std::cout << "\n";
    }
  }
  
  

  std::cout << "\n" << "Uptime: " << LinuxParser::UpTime() << "\n";

  std::cout << "Total processes: " << LinuxParser::TotalProcesses() << "\n";

  std::cout<< "Running Processes: " << LinuxParser::RunningProcesses() << "\n";
  
  LinuxParser::CpuUtilization();



  for(int i = 0; i < LinuxParser::CpuUtilization().size(); i++)
  {
  std::cout << "Cpu Data: " << LinuxParser::CpuUtilization()[i] << "\n";
  }
  
  

 std::cout << "Jiffies: " << LinuxParser::Jiffies() << "\n";
 std::cout << "Active Jiffies: " << LinuxParser::ActiveJiffies() << "\n";
 std::cout << "Idle Jiffies: " << LinuxParser::IdleJiffies() << "\n";

 std::cout << "Uid: " << LinuxParser::Uid(6284) << "\n";

 std::cout << "User: " << LinuxParser::User(6284) << "\n";

 std::cout << "Active PID Jiffies: " << LinuxParser::ActiveJiffies(1) << "\n";

 std::cout << "Command for PID: " << LinuxParser::Command(6284) << "\n";

 std::cout << "PID Uptime: " << LinuxParser::UpTime(1) << "\n";

 std::cout << "PID ram: " << LinuxParser::Ram(6284) << "\n";

 std::cout << "CPU Usage: " << (LinuxParser::ActiveJiffies(1)/sysconf(_SC_CLK_TCK)) * (100 / LinuxParser::UpTime(1)) << "\n";
  

}

*/








