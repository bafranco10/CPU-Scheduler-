#include "FCFS.h"
#include "PCB_Class.h"

FCFS::FCFS()
{
    cpuTime = 0;
}

FCFS::~FCFS()
{
    //dtor
}

void FCFS::startFCFS(bool verbose){
    PCB_Class pcb;
    PCB_Class::PCB block;
    int earliestArrival;

   
    while(!pcb.queueEmpty(pcb.waitQueue)){
 cout << "hey0";

        block = pcb.getPCB(pcb.waitQueue);
        if(block.arrivalTime <= cpuTime){
        cout << "\nat" << block.arrivalTime;
            block.waitTime = cpuTime - block.arrivalTime;
cout << "\nwt" << block.waitTime;
            cpuTime += block.burstTime;
            cout << "\nct" << cpuTime;
            pcb.popQueue(pcb.waitQueue);
            pcb.pushQueue(block, pcb.doneQueue);

        }
        else{
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);
            earliestArrival = pcb.earliestArrival(pcb.waitQueue);
            cout << "\nea" << earliestArrival;
            if(earliestArrival > cpuTime){
                cpuTime = earliestArrival;
            }
        }
    }
      cout << "hey3";
    printOutput(verbose);
    
}

void FCFS::printOutput(bool verbose){
    
    if(!verbose){
        PCB_Class pcb;
        PCB_Class::PCB block;
        int totalWait = 0, wait;
        int processes = pcb.queueSize(pcb.doneQueue);
        
        while(!pcb.queueEmpty(pcb.doneQueue)){
            block = pcb.getPCB(pcb.doneQueue);
            cout << "\nP_" << block.id;

            wait = block.waitTime;
            totalWait += wait;
            cout << "\tWait: " << wait;

            pcb.popQueue(pcb.doneQueue);
        }
        cout << "\n\tAverage Wait: " << (totalWait/(float) processes) << endl;
    }
    else{
        verboseOutput();
    }
}

void FCFS::verboseOutput(void){

}