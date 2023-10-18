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
        };

        queue<PCB> newQueue;
        queue<PCB> readyQueue;
        queue<PCB> waitQueue;
        queue<PCB> doneQueue;

        PCB_Class();
        ~PCB_Class();

        // takes in a PCB line and puts it into newQueue, returns true on success
        bool loadPCB(string fileLine);

        // checks if the values in the given PCB are valid, returns false if no errors found
        bool loadErrorCheck(PCB block);

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

    protected:

    private:
        const char BLANK = ' ', UNDERLINE='_', TAB='\t';

        queue<PCB> sortQueue;

        // returns the index of the first non-blank character in the given string starting at the given position
        // returns -1 if only blanks are found
        int skipBlanks(string& fileLine, int startPos);

        
};

#endif // PCB_CLASS_H
