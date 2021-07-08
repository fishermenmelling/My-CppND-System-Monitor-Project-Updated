#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"



class Processor {
 public:
  
  float Utilization();  // TODO: See src/processor.cpp
  
  void total_setter(float new_prev_total);
  
  void idle_setter(float new_prev_idle);
  
  void non_idle_setter(float new_prev_non_idle);
  
  float non_idle_getter();
  
  float idle_getter();
  
  float total_getter();
  
  std::string system_jiffies;
  std::string idle_jiffies;
  std::string active_jiffies;
  
  
  // TODO: Declare any necessary private members
 private:
  float prev_total = 0;
  float present = 0;
  float prev_idle = 0;
  float prev_non_idle = 0;
  
};

#endif