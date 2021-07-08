#include <string>
#include <iostream>
#include "format.h"
#include "sstream"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int seconds) { 
  long hours = seconds / 60 / 60;
  long minutes = seconds / 60;
  
  while (hours >= 60) {
  	hours -= 60;
  }
  	
  while (minutes >= 60) {
  	minutes -= 60;
  }
  
  
  while (seconds >= 60) {
  	seconds -= 60;
  }
  
  string new_seconds = to_string(seconds);
  
  if (seconds < 10) {
   new_seconds = "0" + to_string(seconds);
  }
  
  
 
  string answer = to_string(hours) + ":" + to_string(minutes) + ":" + new_seconds;
  
  return answer; 
}