// FILE: Priority.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for Priority that contains all functions needed to run the Prioirty algorithm and given flags
//

#ifndef PRIORITY_H
#define PRIORITY_H

#include "PCB_Class.h"

using namespace std;

class Priority{
  
public:
  Priority();
  ~Priority();
  
  // takes in a PCB_Class object, the verbose flag, and the preemption flag and then schedules using Priority
  void prioritySchedule(bool verbose, bool preemption, PCB_Class& pcb);
        
  
protected:
  
private:
  // takes in a PCB_Class object and the verbose flag and then prints out the doneQueue
        void printOutput(PCB_Class& pcb);
  
  // takes in a PCB and prints out its CPU enter and exit times
  void verboseOutput(PCB_Class::PCB block);
};

#endif // PRIORITY_H
