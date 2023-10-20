// FILE: PCB_Class.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for PCB_Class that contains all functions needed to access PCBs and queues of PCBs
//

#ifndef PCB_CLASS_H
#define PCB_CLASS_H

#include <iostream>
#include <queue>

using namespace std;

class PCB_Class{

    public:
        const int PID_TAG=0,ARRIVAL_TAG=1,BURST_TAG=2,PRIORITY_TAG=3;

        struct PCB{
            int pid, priority, burstTime, arrivalTime;
            int waitTime,exitCounter,exitTime,enterTime;
            bool isFirst;
        };

        queue<PCB> initQueue;
        queue<PCB> readyQueue;
        queue<PCB> waitQueue;
        queue<PCB> doneQueue;

        PCB_Class();
        ~PCB_Class();

        void printInitQueue();

        // takes in a queue and a PCB and pushes the PCB into the end of the queue
        void pushQueue(PCB block, queue<PCB>& queue);

        // takes in a queue and pops the next element
        void popQueue(queue<PCB>& queue);

        // takes in a queue and returns the next PCB
        PCB getPCB(queue<PCB>& queue);

        // takes in a queue and returns true if empty
        bool queueEmpty(queue<PCB>& queue);

        // takes in a queue and returns its size
        int queueSize(queue<PCB>& queue);

        // swaps the contents of queue1 and queue2
        void swapQueues(queue<PCB>& queue1, queue<PCB>& queue2);

        // retuns the PCB with the most significant value of the given tag within the given queue
        // PID_TAG - smallest pid   ARRIVAL_TAG - earliest arrival 
        // BURST_TAG - shortest burst   PRIORITY_TAG - highest priority
        PCB findTagPCB(queue<PCB>& queue, int tag);

        // takes in a queue and sorts it on the given tag in
        // PID_TAG - ascending   ARRIVAL_TAG - ascending 
        // BURST_TAG - ascending   PRIORITY_TAG - descending
        void queueTagSort(queue<PCB>& queue, int tag);

        // removes the entered block from the given queue
        void removeBlock(PCB block, queue<PCB>& queue);

        // takes in a queue and cpuTime and then pushes the next available process
        void makeReady(queue<PCB>& queue, int cpuTime);

        void makeReadyRR(queue<PCB>& inputQueue, int cpuTime);

        void printReadyQueue();
  
    protected:

    private:

        queue<PCB> sortQueue;
        
};

#endif // PCB_CLASS_H
