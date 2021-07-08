#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::vector;
using std::string;

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  vector<Process>& Processes();  	  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  string Kernel();               	  // TODO: See src/system.cpp
  string OperatingSystem();      	  // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  //object from processor class
  Processor cpu_ = {};
  
  vector<Process> processes_ = {};
};

#endif