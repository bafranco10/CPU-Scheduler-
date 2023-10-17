#include "roundRobin.h"
#include "PCB_Class.h"
#include <queue>
#include "roundRobin.h"
#include "PCB_Class.h"
#include <queue>

roundRobin::roundRobin(int quantum) : cpuTime(0), timeQuantum(quantum) {
}

roundRobin::~roundRobin() {
    // Destructor
}

void roundRobin::startRoundRobin(bool verbose) {
    PCB_Class pcb;
    PCB_Class::PCB block;

    while (!pcb.queueEmpty(pcb.waitQueue)) {
        block = pcb.getPCB(pcb.waitQueue);
        if (block.burstTime <= timeQuantum) {
            // Process can complete in this quantum
            block.waitTime = cpuTime - block.arrivalTime;
            cpuTime += block.burstTime;
            pcb.popQueue(pcb.waitQueue);
            pcb.pushQueue(block, pcb.doneQueue);
        } else {
            // Process needs more quantum time
            block.waitTime = cpuTime - block.arrivalTime;
            cpuTime += timeQuantum;
            block.burstTime -= timeQuantum;
            pcb.pushQueue(block, pcb.waitQueue);
            pcb.popQueue(pcb.waitQueue);
        }
    }
    printOutput(verbose);
}

void roundRobin::printOutput(bool verbose) {
    if (!verbose) {
        PCB_Class pcb;
        PCB_Class::PCB block;
        int totalWait = 0, wait;
        int processes = pcb.queueSize(pcb.doneQueue);

        while (!pcb.queueEmpty(pcb.doneQueue)) {
            block = pcb.getPCB(pcb.doneQueue);
            cout << "\nP_" << block.id;

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
