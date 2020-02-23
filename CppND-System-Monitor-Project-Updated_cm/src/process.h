#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

//Include LinuxParser namespace

class Process  {
 public:
 // Add constructor to populate all attributes for PID instance upon creation and store into process vector
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
 int PID;
 float CpuUtil;
 long cpu_usage {};
 std::string command = " ";
 std::string ram;
 std::string user = " ";
 std::string upTime;
};

#endif