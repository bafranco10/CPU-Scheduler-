#ifndef FCFS_H
#define FCFS_H


class FCFS{

    public:
        FCFS();
        ~FCFS();

        int cpuTime,processes;

        void startFCFS(bool verbose);
        void printOutput(bool verbose);
        void verboseOutput(void);

    protected:

    private:
        
};

#endif // FCFS_H
