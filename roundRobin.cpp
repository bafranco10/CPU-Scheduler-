// FILE: roundRobin.cpp
// Brian Franco, Armando Bautista, Estefan Mora
// OS, Fall 2023, Transy U
// Round Robin Implementation

#include "roundRobin.h"
#include "PCB_Class.h"
#include <queue>

roundRobin::roundRobin() {

}

roundRobin::~roundRobin() {
    // Destructor
}
// takes in verbose a quantum and a set of PCB blocks
// Returns each process wait time as well as prints queues necessary for debugging. 
// also it does cpu scheduling in round robin format
void roundRobin::rrSchedule(bool verbose, int quantum, PCB_Class& pcb) {
    PCB_Class::PCB block;
    int cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue);
    // Keep looping until all processes are in doneQueue
    while (pcb.queueSize(pcb.doneQueue) != initSize) {
        // Move all ready processes from initQueue to readyQueue
        int initQueueSize = pcb.queueSize(pcb.initQueue);
        for (int i = 0; i < initQueueSize; ++i) {
            // gets first process in list
            PCB_Class::PCB firstProcess = pcb.getPCB(pcb.initQueue);
            if (firstProcess.arrivalTime <= cpuTime) {
                pcb.pushQueue(firstProcess, pcb.readyQueue);
                // Makes sure to remove the process from initQueue
                pcb.popQueue(pcb.initQueue);
                pcb.printInitQueue();

            }
        }
        // If readyQueue is not empty move to next ready process
        if (!pcb.queueEmpty(pcb.readyQueue)) {
            block = pcb.getPCB(pcb.readyQueue);
            if (verbose) {
            cout << "P" << block.pid << " Enter " << cpuTime << endl;
            pcb.printReadyQueue();
        }
            // if burst time is greater than quantum calculate wait time and how much time is left for process to finish
            // also keep track of when the process left
            if (block.burstTime > quantum) {
                block.burstTime -= quantum;
                if (verbose) {
                cout << "process: " << block.pid << " burst time:" << block.burstTime <<endl;
            }

                calcWait(block, cpuTime);

                cpuTime += quantum;

                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.readyQueue);
                pcb.popQueue(pcb.readyQueue);
            }
            // if process is less than quantum then increment cpuTime by burst time that process had left  
            else {
                int newQuantum = block.burstTime;
                block.burstTime = 0; // Process completes

                calcWait(block, cpuTime);

                cpuTime += newQuantum;
                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.doneQueue);
                pcb.printDoneQueue();
                pcb.popQueue(pcb.readyQueue);
            }
            if (verbose) {
            cout << "P" << block.pid << " Exit " << block.exitTime << endl;
        }
        }
        // if readyQueue is empty increment cpuTime by 1 till another process is ready
        else 
            {
                cpuTime++;
                } 
    }
    printOutput(verbose, pcb);
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

// takes in a pcb block and a cpu time and returns the wait time 
void roundRobin::calcWait(PCB_Class::PCB& block, int cpuTime){
    // if block enters for first time wait = cpu time - arrivalTime which
    //otherwise it is equal to cpuTime - last exit
    if(block.exitCounter==0){
        block.waitTime += cpuTime - block.arrivalTime;
    }
    else{
        block.waitTime += cpuTime - block.exitTime;
    }
}
