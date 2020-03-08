# Implementing Syscalls and Scheduling policies for xv6



## For running the program run the command 

    > make qemu [SCHEDPOLICY=POLICY]  

The POLICY used can be either FCFS, MLFQ or PBS. However, please note that, before switching between policies, do "make clean" once

## Waitx SYSCALL

To implement this function, we added creation time (ctime), Runtime (rtime), and Endtime (etime) to the proc structures. This function just does as mentioned in the PDF, that is assign the total number of clock ticks during which process was waiting and total number of clock ticks when the process was running. This function returns 0 for success and -1 for failure that is, no child process found to kill.


## Implementation of FCFS 

Here, in FCFS (First Come First Serve), we recurse over the ptable and find the running proc with oldest ctime, and execute it first. 

## Implementation of PBS 

Here in PBC (Priority Based Scheduling), we added a new parameter, called priority to the proc structure. Then we recurse over the ptable to find the running proc with highest priority and make it run like in FCFS. In order to set the priority of a process, we use the SYSCALL int setpriority(int priority).


## Implementation of Getpinfo SYSCALL

We need getpinfo SYSCALL to check the details regarding the process passed to it. It returns 0 for success, i.e. process exists and -1 otherwise

## Implementation of MLFQ 

Here in MLFQ (Multi-level Feedback Queue) scheduling, we create multiple(5) queues. In each queue, each process is alloted a particular number of ticks. If the process fails to execute within that time it is demoted to the next queue. Aging implemented, ensures that no process will wait in the lowest priority queue indefinitely.

## Comparison between the different scheduling algorithms

In order to compare the scheduling algorithms, run the benchmark command. We get the following observations:  
    -MLFQ and default implement scheduling in the fastest way
    -MLFQ algorithm, though it is elaborate and difficult to implement, is fast as it handles almost all cases and gives best response time and throughput. 
    -PBS gives a very good response time for real time applications.
    -FCFS is the slowest but it is really easy to implement.

However, in the Implementation of XV6, trap always preempt the running process after each tick. This prevents the MLFQ and all other algorithms from working properly.

## Benchmark Result Data
## Run data of DEFAULT
```
	test 3 ended
	wait = 232 run = 456
	test 1 ended
	wait = 230 run = 492
	test 2 ended
	wait = 255 run = 562
```

## Run data of FCFS
```
	Creation Time: test1 > test3 > test2
	test 1 ended
	wait = 1 run = 518
	test 3 ended
	wait = 263 run = 487
	test 2 ended
	wait = 272 run = 516
```

## Run data of PBS
```
	Priority: test2 > test 1 > test 3
	test 1 ended
	wait = 0 run = 498
	test 3 ended
	wait = 2 run = 504
	test 2 ended
	wait = 273 run = 518
```

## Run data of MLFQ
```
	test 2 ended
	PID == 9
	Run_time = 492
	Num_run = 962
	current_queue=5
	ticks : 2 2 4 8 9 
	wait = 251 run = 494

	test 1 ended
	PID == 7
	Run_time = 519
	Num_run = 1016
	current_queue=5
	ticks : 2 2 4 8 9 
	wait = 252 run = 520

	test 3 ended
	PID == 8
	Run_time = 528
	Num_run = 1034
	current_queue=5
	ticks : 2 2 4 8 9 
	wait = 259 run = 529
```
