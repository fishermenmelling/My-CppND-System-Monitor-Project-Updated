#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

using std::string;
using std::vector;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int new_count): count(new_count) {}
  int Pid();                               // TODO: See src/process.cpp
  string User();                           // TODO: See src/process.cpp
  string Command();                        // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  string Ram();                       	   // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  int count;
  long int uptime = UpTime();
  float cpu_usage = CpuUtilization();
  // TODO: Declare any necessary private members
 private:
  int b;
  
};

#endif