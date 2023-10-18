// FILE: roundRobin.cpp
// Brian Franco, Armando Bautista, Estefan Mora
// OS, Fall 2023, Transy U
// Round Robin Implementation

#include "roundRobin.h"
#include "PCB_Class.h"
#include <queue>

/*
roundRobin::roundRobin(int quantum) : cpuTime(0), timeQuantum(quantum) {
}
//*/

roundRobin::roundRobin() {

}

roundRobin::~roundRobin() {
    // Destructor
}

void roundRobin::startRoundRobin(bool verbose, int quantum, PCB_Class& pcb) {
    PCB_Class::PCB block;
    int cpuTime = 0;

    while (!pcb.queueEmpty(pcb.waitQueue)) {
        block = pcb.getPCB(pcb.waitQueue);
        if (block.burstTime <= quantum) {
            // Process can complete in this quantum
            block.waitTime = cpuTime - block.arrivalTime;
            cpuTime += block.burstTime;
            pcb.popQueue(pcb.waitQueue);
            pcb.pushQueue(block, pcb.doneQueue);
        } else {
            // Process needs more quantum time
            block.waitTime = cpuTime - block.arrivalTime;
            cpuTime += quantum;
            block.burstTime -= quantum;
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);
        }
    }
    printOutput(verbose,pcb);
}

// doesn't work yet, but prints out something
void roundRobin::rrSchedule(bool verbose, int quantum, PCB_Class& pcb){
    PCB_Class::PCB block;
    int earliestArrival,cpuTime = 0;

    pcb.queueTagSort(pcb.waitQueue,pcb.PID_TAG);

    while (!pcb.queueEmpty(pcb.waitQueue)) {

        block = pcb.getPCB(pcb.waitQueue);
        if(block.arrivalTime <= cpuTime){
            if (block.burstTime > quantum) {
                block.burstTime -= quantum;

                block.enterTime = cpuTime;

                cpuTime += quantum;

                block.exitTime = cpuTime;
                block.exitCounter++;

                block.waitTime += block.exitTime - block.enterTime;

                pcb.pushQueue(block, pcb.waitQueue);
                pcb.popQueue(pcb.waitQueue);
            } 
            else{
                block.enterTime = cpuTime;

                cpuTime += block.burstTime;

                block.exitTime = cpuTime;
                block.exitCounter++;

                block.waitTime += block.exitTime - block.enterTime;

                pcb.popQueue(pcb.waitQueue);
                pcb.pushQueue(block, pcb.doneQueue);
            }
        }
        else{
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);

            earliestArrival = pcb.findTagPCB(pcb.waitQueue,pcb.ARRIVAL_TAG).arrivalTime;
            if(earliestArrival > cpuTime){
                cpuTime = earliestArrival;
            }
        }
    }
    printOutput(verbose,pcb);
}
 
void roundRobin::printOutput(bool verbose, PCB_Class& pcb) {
    if (!verbose) {
        PCB_Class::PCB block;
        int totalWait = 0, wait;
        int processes = pcb.queueSize(pcb.doneQueue);

        pcb.queueTagSort(pcb.doneQueue,pcb.PID_TAG);

        while (!pcb.queueEmpty(pcb.doneQueue)) {
            block = pcb.getPCB(pcb.doneQueue);
            cout << "\nP_" << block.pid;

            wait = block.waitTime;
            totalWait += wait;
            cout << "\tWait: " << wait;

            pcb.popQueue(pcb.doneQueue);
        }
        cout << "\n\tAverage Wait: " << (totalWait / (float)processes) << endl;
    } else {
        verboseOutput();
    }
}

void roundRobin::verboseOutput() {
   
}
