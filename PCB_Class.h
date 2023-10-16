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
            int id, priority, burstTime, arrivalTime;
            bool waiting;
        };

        queue<PCB> newQueue;
        queue<PCB> readyQueue;
        queue<PCB> waitQueue;

        PCB_Class();
        ~PCB_Class();

        // takes in a PCB line and puts it into a queue
        void loadPCB(string fileLine, queue<PCB>& initialQueue);
        void pushQueue(PCB block, queue<PCB>& queue);
        void popQueue(queue<PCB>& queue);
        PCB getPCB(queue<PCB>& queue);
        bool queueEmpty(queue<PCB> queue);
        

        
    protected:

    private:
        const char BLANK = ' ', UNDERLINE='_';

        
};

#endif // PCB_CLASS_H
