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

void Priority::prioritySchedule(bool verbose, bool preemption, PCB_Class& pcb){
    PCB_Class::PCB block;
    FCFS fcfs;

    if(!preemption){
        fcfs.fcfsSchedule(verbose,pcb,pcb.PRIORITY_TAG);
    }
    else{

    }
}

void Priority::printOutput(bool verbose, PCB_Class& pcb){
    
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

        if(verbose){
            verboseOutput(block);
        }

        pcb.popQueue(pcb.doneQueue);
    }
    cout << "\n\tAverage Wait: " << (totalWait/(float) processes) << endl; 
}

void Priority::verboseOutput(PCB_Class::PCB block){
    int cpuTime = block.waitTime + block.arrivalTime;
    cout << " \tCPU Entered: " << cpuTime
        << " CPU Left: " << (block.burstTime + cpuTime);
}