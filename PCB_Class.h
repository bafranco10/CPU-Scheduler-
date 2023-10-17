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

        // takes in a PCB line and puts it into newQueue
        void loadPCB(string fileLine);
        void pushQueue(PCB block, queue<PCB>& queue);
        void popQueue(queue<PCB>& queue);
        PCB getPCB(queue<PCB>& queue);
        bool queueEmpty(queue<PCB>& queue);
        int queueSize(queue<PCB>& queue);

        // retuns the smallest arrival time within the given queue
        int earliestArrival(queue<PCB>& queue);

        // retuns the smallest pid time within the given queue
        int smallestPid(queue<PCB>& queue);
        int shortestJob(queue<PCB>& queue);
        int highestPriority(queue<PCB>& queue);

    protected:

    private:
        const char BLANK = ' ', UNDERLINE='_';

        int skipBlanks(string fileLine, int startPos);

        
};

#endif // PCB_CLASS_H
