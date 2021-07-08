#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"
#include "system.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { 
  
  vector<int> pids = LinuxParser::Pids();
  
  return pids[count];
    
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
 
  return LinuxParser::ActiveJiffies(Process::Pid()); }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid());}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  
  return a.cpu_usage < cpu_usage;
   
}