// FILE: FCFS.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for FCFS that contains all functions needed to run the FCFS algorithm and given flags
//

#include "FCFS.h"
#include "PCB_Class.h"

using namespace std;

FCFS::FCFS(){
}

FCFS::~FCFS(){
}

void FCFS::fcfsSchedule(bool verbose, PCB_Class& pcb, int tag){
    PCB_Class::PCB block;
    int earliestArrival,cpuTime = 0;

    pcb.queueTagSort(pcb.waitQueue,tag);

    while(!pcb.queueEmpty(pcb.waitQueue)){

        block = pcb.getPCB(pcb.waitQueue);
        if(block.arrivalTime <= cpuTime){
            block.enterTime = cpuTime;
            block.waitTime = block.enterTime - block.arrivalTime;

            cpuTime += block.burstTime;

            block.exitTime = cpuTime;
            block.exitCounter++;

            pcb.popQueue(pcb.waitQueue);
            pcb.pushQueue(block, pcb.doneQueue);
        }
        // if process has not arrived yet move it to back of queue
        else{
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);

            earliestArrival = pcb.findTagPCB(pcb.waitQueue,pcb.ARRIVAL_TAG).arrivalTime;
            // if no other processes can run, then set cputTime to the next arrival
            if(earliestArrival > cpuTime){
                cpuTime = earliestArrival;
            }
        }
    }
    printOutput(verbose, pcb);
}

void FCFS::printOutput(bool verbose, PCB_Class& pcb){
    
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

void FCFS::verboseOutput(PCB_Class::PCB block){
    int cpuTime = block.waitTime + block.arrivalTime;
    cout << " \tCPU Entered: " << block.enterTime
        << " CPU Left: " << block.exitTime;
}
