#ifndef PCB_CLASS_H
#define PCB_CLASS_H

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class PCB_Class{

    public:
        //const int NEW_STATUS=0, READY_STATUS=1,RUNNING_STATUS=2,WAITING_STATUS=3,TERMINATED_STATUS=4;

        struct PCB{
            int pid, priority, burstTime, arrivalTime;
            int waitTime;
            bool waiting;
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

        // retuns the PCB with the smallest arrival time within the given queue
        PCB earliestArrival(queue<PCB>& queue);

        // retuns the PCB with the smallest pid time within the given queue
        PCB smallestPid(queue<PCB>& queue);

        // return the PCB with the shortest CPU burst in the given queue
        PCB shortestJob(queue<PCB>& queue);

        // returns the PCB with the highest prioirty in the given queue
        PCB highestPriority(queue<PCB>& queue);

        // takes in a queue and sorts it on pid in ascending order
        void sortPid(queue<PCB>& queue);

    protected:

    private:
        const char BLANK = ' ', UNDERLINE='_', TAB='\t';

        // returns the index of the first non-blank character in the given string starting at the given position
        // returns -1 if only blanks are found
        int skipBlanks(string& fileLine, int startPos);

        
};

#endif // PCB_CLASS_H
