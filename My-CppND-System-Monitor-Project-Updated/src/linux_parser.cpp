#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "format.h"
#include "linux_parser.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::ifstream;
using std::getline;
using std::istringstream;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
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
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
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
  ifstream file(kProcDirectory + kMeminfoFilename);
  float number, memtotal, memfree;
  
  string line, other_line;
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream whole_line(line);
      int i;

      while (whole_line >> other_line >> number) {
         if(other_line == "MemTotal:"){
            memtotal = number;
         }
         if(other_line == "MemFree:"){
            memfree = number;
         }

		i++;
      }


    }
  }
  float totalmemused = memtotal - memfree;
    
  return totalmemused / memtotal;

}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  ifstream file(kProcDirectory + kUptimeFilename);
  long line;
  file >> line;
  return line; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  //this doesn't really do anything
  Processor processor;
  return stol(processor.system_jiffies); 

}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::ActiveJiffies(int pid) { 
  
  ifstream  file(kProcDirectory + to_string(pid) + kStatFilename);
  string number, utime, stime, cutime, cstime;
  float total_time;
  float seconds;
  float cpu_use;
  int i = 0;
  while(file >> number) {
  	switch(i) {
      case 14:
      	utime = number;
      break;
      case 15:
        stime = number;
      break;
      case 16:
      	cutime = number;
      break;
      case 17:
        cstime = number;
      break;
    }
    i++;
  }
  
  total_time = stof(utime) + stof(stime) + stof(cutime) + stof(cstime);
  
  seconds = LinuxParser::UpTime(pid);
     
  
     
  cpu_use = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
     
  return cpu_use;
  
  
                                                         
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  //this doesn't really do anything
   Processor processor;
  return stol(processor.active_jiffies);
              
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  //this doesn't really do anything
  Processor processor;
  return stol(processor.idle_jiffies);
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  return {}; 

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  ifstream file(kProcDirectory + kStatFilename);
  string line, other_line;
  int number;
  while (getline(file, line)) {
  	istringstream whole_line(line);
    while (whole_line >> other_line >> number) {
       if(other_line == "processes"){
      	return number;
       }
    }
  }
  	return number;
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  ifstream file(kProcDirectory + kStatFilename);
  string line, other_line;
  int number;
  while (getline(file, line)) {
  	istringstream whole_line(line);
    while (whole_line >> other_line >> number) {
       if(other_line == "procs_running"){
      	return number;
       }
    }
  }
  	return number;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
 
 ifstream  file(kProcDirectory + to_string(pid) + kCmdlineFilename);
 string line;
 getline(file, line);
 return line; 
                                                     
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  ifstream  file(kProcDirectory + to_string(pid) + kStatusFilename);
  string line;
  int ram;
  while (file >> line) {
   if (line == "VmSize:") {
    file >> ram; 
   }
  }
  //kb > mb
  return to_string(ram / 1000); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  ifstream  file(kProcDirectory + to_string(pid) + kStatusFilename);
  string line, uid;
  while (file >> line) {
   if (line == "Uid:") {
    file >> line >> uid; 
   }
  }
  
  return uid; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  ifstream  file(kPasswordPath);
  string line, username;
  while (getline(file, line)) {
  	
    std::replace(line.begin(), line.end(), ':', ' ');
    string name, x = "x", number;
    std::istringstream linestream(line);
    linestream >> name >> x >> number;
    
    if (number == LinuxParser::Uid(pid)) {
    	username = name;
    }
 
  }
  
  return username; 

}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  ifstream file(kProcDirectory + to_string(pid) + kStatFilename);
  int i = 0;
  string number;
  while (file >> number) {
  	if (i == 21) {
     return LinuxParser::UpTime() - (stoi(number) / sysconf(_SC_CLK_TCK));
    }
    i++;
  }
  return 0;
}
