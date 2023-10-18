# FILE: makefile
# A Bautista, B Franco, E Mora
# OS, Fall 2023, Transy U
#
# makefile for Group 3 CPU_Scheduler
#

CPU_Scheduler: CPU_Scheduler.o PCB_Class.o FCFS.o roundRobin.o Priority.o SJF.o
	g++ CPU_Scheduler.o PCB_Class.o FCFS.o roundRobin.o Priority.o SJF.o -o CPU_Scheduler
	
CPU_Scheduler.o: CPU_Scheduler.cpp PCB_Class.h FCFS.h roundRobin.h SJF.h Priority.h
	g++ -c CPU_Scheduler.cpp

PCB_Class.o: PCB_Class.cpp PCB_Class.h
	g++ -c PCB_Class.cpp

FCFS.o: FCFS.cpp FCFS.h PCB_Class.h
	g++ -c FCFS.cpp

roundRobin.o: roundRobin.cpp roundRobin.h PCB_Class.h
	g++ -c roundRobin.cpp

Priority.o: Priority.cpp Priority.h PCB_Class.h FCFS.h
	g++ -c Priority.cpp

SJF.o: SJF.cpp SJF.h PCB_Class.h FCFS.h
	g++ -c SJF.cpp
