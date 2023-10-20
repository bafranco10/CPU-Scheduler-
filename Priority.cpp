// FILE: Priority.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for Priority that contains all functions needed to run the Priority algorithm and given flags
//

#include "Priority.h"
#include "FCFS.h"
#include "PCB_Class.h"

using namespace std;

Priority::Priority(){
}

Priority::~Priority(){
}

// takes in verbose flag, preemptive flag, and a set of pcbs
// it then returns average wait time of processes scheduled with a priority queue depending on preemption flag
void Priority::prioritySchedule(bool verbose, bool preemption, PCB_Class& pcb){
  PCB_Class::PCB block;
    FCFS fcfs;
    int cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue);
    // if not preemptive use fcfs sorted by priority
    if(!preemption){
        fcfs.fcfsSchedule(verbose,pcb,pcb.PRIORITY_TAG);
    }
    
    // sort by finding item with highest priority and then check priorities again after completion of a process

    else{
      int cpuTime = 0;
      PCB_Class::PCB currentProcess;
      bool isProcessRunning = false;
      
      // sort processes by arrival time
      pcb.queueTagSort(pcb.initQueue, pcb.ARRIVAL_TAG);
      
      while (!pcb.queueEmpty(pcb.initQueue) || !pcb.queueEmpty(pcb.readyQueue) || isProcessRunning) {
	// Move processes from initQueue to readyQueue based on arrival time
        pcb.makeReadySJF(pcb.initQueue, cpuTime);

	if (verbose) {

	  cout << "P_" << currentProcess.pid << " Enter: " << cpuTime;
        }
	
        if (!pcb.queueEmpty(pcb.readyQueue)) {
	  if (isProcessRunning) {
	    PCB_Class::PCB highestPriority = pcb.findTagPCB(pcb.readyQueue, pcb.PRIORITY_TAG);
	    // if the highestPriority item in ready queue is greater than currentProcess then replace that process
	    //with the highestPriority process that we found
	    if (highestPriority.priority > currentProcess.priority) {
	      pcb.pushQueue(currentProcess, pcb.readyQueue);
	      currentProcess = highestPriority;
	      
	      pcb.removeBlock(currentProcess, pcb.readyQueue);
	    }
	  }
	  // else currentProcess stays the same
	  else {
	    currentProcess = pcb.findTagPCB(pcb.readyQueue, pcb.PRIORITY_TAG);
	    pcb.removeBlock(currentProcess, pcb.readyQueue);
	    isProcessRunning = true;
	  }
        }
	
        // update process wait times in ready queue
        std::queue<PCB_Class::PCB> tempQueue;
        while (!pcb.queueEmpty(pcb.readyQueue)) {
	  PCB_Class::PCB processInQueue = pcb.getPCB(pcb.readyQueue);
	  
	  if (processInQueue.pid != currentProcess.pid) {
	    processInQueue.waitTime++;
	  }
	    
	  tempQueue.push(processInQueue);
	  pcb.popQueue(pcb.readyQueue);
        }
	
        // swap tempqueue and actual queue
        while (!tempQueue.empty()) {
	  pcb.pushQueue(tempQueue.front(), pcb.readyQueue);
	  tempQueue.pop();
        }
	
        if (isProcessRunning) {
	  currentProcess.burstTime--;
	  
	  if (currentProcess.burstTime == 0) {
	    // Set the exitTime when the process is completed
	    currentProcess.exitTime = cpuTime + 1;  // Update the exitTime
	    
	    pcb.pushQueue(currentProcess, pcb.doneQueue); 
	    isProcessRunning = false;
	  }
	  if (verbose) {
	    cout << " Exit: " << currentProcess.exitTime << endl;
	  }
	  
        }
	
        cpuTime++;
      }
      printOutput(pcb);
    }
    
}

void Priority::printOutput(PCB_Class& pcb){
  
  PCB_Class::PCB block;
  int totalWait = 0, wait;
  int processes = pcb.queueSize(pcb.doneQueue);
  
  pcb.queueTagSort(pcb.doneQueue,pcb.PID_TAG);
    
    while(!pcb.queueEmpty(pcb.doneQueue)){
      block = pcb.getPCB(pcb.doneQueue);
      cout << "\nP_" << block.pid;
      
        wait = block.waitTime;
        totalWait += wait;
        cout << "\tWait: " << wait;
	
        pcb.popQueue(pcb.doneQueue);
    }
    cout << "\n\tAverage Wait: " << (totalWait/(float) processes) << endl; 
}
