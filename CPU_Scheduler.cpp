// FILE: CPU_Scheduler.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Driver for CPU_Scheduler that reads in a file and interprets input to select a scheduling algoirithm to use
//
// https://cplusplus.com/reference/queue/queue/ 10-15-2023
//

#include "PCB_Class.h"
#include "FCFS.h"
#include "Priority.h"
#include "SJF.h"
#include "roundRobin.h"
#include <iostream>
#include <fstream>
using namespace std;

const string TYPE="--type", PREEMPTIVE="--preemptive", QUANTA="--quanta",FILE_NAME="--file",VERBOSE="--verbose";
const string FIRST_COME_FIRST_SERVE="FCFS",SHORTEST_JOB_FIRST="SJF",PRIORITY="Priority",ROUND_ROBIN="RR";
const string DEFAULT_TYPE=FIRST_COME_FIRST_SERVE,DEFAULT_QUANTA="10",DEFAULT_FILE="sched.in";
const int FLAGS=5,TYPE_FLAG=0,PREEMPTIVE_FLAG=1,QUANTA_FLAG=2,FILE_FLAG=3,VERBOSE_FLAG=4;

// checks if input is valid and returns false if no errors found
bool errorCheck(bool *flags, char **argv, string type, string quanta);

// checks if command line set up is valid and returns false if no isses found
bool commandCheck(int argc, char**argv);

int main(int argc, char **argv){
		PCB_Class pcb;
		FCFS fcfs;
		SJF sjf;
		Priority pri;
		roundRobin rr;

		ifstream inputFile;
		string fileLine;
		string type = DEFAULT_TYPE, quanta = DEFAULT_QUANTA, fileName = DEFAULT_FILE;
		bool flags[FLAGS];

		for(int i=0;i<FLAGS;i++) flags[i]=false;

		if(commandCheck(argc, argv)) return 0;

        // check for ----type find TYPE then if found, but not TYPE, error
		for(int i=0;i<argc;i++){
            string argument = argv[i];
			if(argument == TYPE){
				type = argv[i+1];
                flags[TYPE_FLAG] = true;
			}
			if(argument == PREEMPTIVE){
                flags[PREEMPTIVE_FLAG] = true;
			}
			if(argument == QUANTA){			
				quanta = argv[i+1];
            	flags[QUANTA_FLAG] = true;              
			}
			if(argument == FILE_NAME){
				fileName = argv[i+1];
            	flags[FILE_FLAG] = true;                
			}
			if(argument == VERBOSE){
                flags[VERBOSE_FLAG] = true;
			}
		}
		
		if(!errorCheck(flags, argv, type, quanta)){
			inputFile.open(fileName);
			if(inputFile){
			    while(!inputFile.eof()){
			        getline(inputFile, fileLine);
					if(!pcb.loadPCB(fileLine)){
						return 0;
					}
				}
				inputFile.close();
			}
			else{
				cout << "\tERROR: File not opened\n";
				return 0;
			}
		}
		else{
			return 0;
		}

		if(type==FIRST_COME_FIRST_SERVE){
			fcfs.fcfsSchedule(flags[VERBOSE_FLAG],pcb,pcb.PID_TAG);
		}
		else if(type==SHORTEST_JOB_FIRST){
			sjf.sjfSchedule(flags[VERBOSE_FLAG],flags[PREEMPTIVE_FLAG],pcb);
		}
		else if(type==PRIORITY){
			pri.prioritySchedule(flags[VERBOSE_FLAG],flags[PREEMPTIVE_FLAG],pcb);
		}
		else if(type==ROUND_ROBIN){
			rr.rrSchedule(flags[VERBOSE_FLAG],atoi(quanta.c_str()),pcb);
		}

	return 0;
}

bool errorCheck(bool *flags, char **argv, string type, string quanta){
	bool error = false;
	if(flags[PREEMPTIVE_FLAG] && type == FIRST_COME_FIRST_SERVE){
		cout << "\tERROR: FCFS cannot be preemptive\n";
		error = true;
	}
	if(type==ROUND_ROBIN && !flags[PREEMPTIVE_FLAG]){
		cout << "\tERROR: RR must be preemptive\n";
		error = true;
	}
	if(type!=ROUND_ROBIN && flags[QUANTA_FLAG]){
		cout << "\tERROR: Only RR should use a quanta specification\n";
		error = true;
	}
	if(type!=ROUND_ROBIN && type!=FIRST_COME_FIRST_SERVE && type!=PRIORITY && type!=SHORTEST_JOB_FIRST){
		cout << "\tERROR: Invlaid type. This program supports FCFS, SJF, Priority and RR\n";
		error = true;
	}
	if(flags[QUANTA_FLAG] && (atoi(quanta.c_str()) <= 0)){
		cout << "\tERROR: Quanta must be a positive number\n";
		error = true;
	}
	return error;		
}

bool commandCheck(int argc, char**argv){
	bool error = false;

	if(argv[argc-1]==TYPE){
		cout << "\tERROR: " << TYPE << " requires an input\n";
		error = true;
	}
	else if(argv[argc-1]==TYPE){
		cout << "\tERROR: " << QUANTA << " requires an input\n";
		error = true;
	}
	else if(argv[argc-1]==TYPE){
		cout << "\tERROR: " << FILE_NAME << " requires an input\n";
		error = true;
	}
	return error;
}
