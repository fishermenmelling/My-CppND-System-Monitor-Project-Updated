#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include "linux_parser.h"

using std::ifstream;
using std::string;
using std::istringstream;
using std::to_string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  
  ifstream file("/proc/stat");
  string line, other_line; 
  
  float user = 0, 
  nice = 0, 
  system = 0, 
  idle = 0, 
  total = 0,
  non_idle = 0,
  totald = 0,
  idled = 0; 
  if (file.is_open()){
    while (getline(file, line)) {

      istringstream whole_line(line);

      while (whole_line >> other_line >> user >> nice >> system >> idle) {

        if(other_line == "cpu") {

          idle_jiffies = to_string(idle);

          /*
          PrevIdle = previdle + previowait
          Idle = idle + iowait
          */
          prev_idle = idle_getter();
          prev_non_idle = non_idle_getter();
          prev_total = total_getter();


          /*
            PrevNonIdle = prevuser + prevnice + prevsystem
            NonIdle = user + nice + system
          */

          non_idle = user + nice + system;

          active_jiffies = to_string(non_idle);


          /*
          PrevTotal = PrevIdle + PrevNonIdle
          Total = Idle + NonIdle

          */

          total = non_idle + idle;

          system_jiffies = to_string(total);

          prev_total = prev_idle + prev_non_idle;
          /*
            differentiate: actual value minus the previous one
            totald = Total - PrevTotal
            idled = Idle - PrevIdle
          */
          totald = total - prev_total;
          idled = idle - prev_idle;

          /*
          CPU_Percentage = (totald - idled)/totald
          */

          non_idle_setter(non_idle); 
          total_setter(total); 
          idle_setter(idle);
		  if (totald != 0) {
          	return (totald - idled) / totald;
          }
        }
      }
    }
  }
  return 0;
}



  void Processor::total_setter(float new_prev_total) {
  	prev_total = new_prev_total;
  }
  
  void Processor::idle_setter(float new_prev_idle) {
  	prev_idle = new_prev_idle;
  }
  
  void Processor::non_idle_setter(float new_prev_non_idle) {
  	prev_non_idle = new_prev_non_idle;
  }
  
  float Processor::non_idle_getter() {
  	return prev_non_idle;
  }
  
  float Processor::idle_getter() {
   	return prev_idle;
  }
  
  float Processor::total_getter() {
  	return prev_total;
  }