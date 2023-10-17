#include "FCFS.h"
#include "PCB_Class.h"



using namespace std;

FCFS::FCFS(){
}

FCFS::~FCFS(){
}

void FCFS::fcfsSchedule(bool verbose, PCB_Class& pcb){
    //PCB_Class pcb;
    PCB_Class::PCB block;
    int earliestArrival,cpuTime = 0;

    while(!pcb.queueEmpty(pcb.waitQueue)){

        block = pcb.getPCB(pcb.waitQueue);
        if(block.arrivalTime <= cpuTime){
            block.waitTime = cpuTime - block.arrivalTime;

            cpuTime += block.burstTime;

            pcb.popQueue(pcb.waitQueue);
            pcb.pushQueue(block, pcb.doneQueue);

        }
        else{
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);

            earliestArrival = pcb.earliestArrival(pcb.waitQueue).arrivalTime;
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
    cout << " \tCPU Entered: " << cpuTime
        << " CPU Left: " << (block.burstTime + cpuTime);
}