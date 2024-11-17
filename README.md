# Operating-Systems

fcfs.c -> CPU scheduling using First Come First Serve
sjf.c -> CPU scheduling using Shortest Burst time first
srtf.c -> Preemptive SJF CPU scheduling
priority.c -> CPU Scheduling using priority(least is given first preference) non-preemptive
priority_prem.c -> CPU scheduling using priority but preemptive
round_robin.c -> CPU scheduling using round robin implemented with queue
banker.c -> Bankers Algorithm to detect deadlock or safe sequence
pc.c -> Process Synchronization done using Pthreads which is showcased by changing the value of counter in critical section
ipc.c -> Inter Process Communication demonstrated between Parent and Child processes by creating an Ordinary Pipe
pc.c -> Producer Consumer Problem demonstrated using semaphores where buffer size and items as input
rw.c -> Readers writers problem demonstrated using semaphores
dp.c -> Dining Philosophers problem demonstrated using semaphores where condition to avoid deadlock are included (both forks available before eating)
part.c -> Static Partitioning - Gets memory partitions and processes as input and return the processes allocated to each block as output based on first fit, best fit and worst fit
var_part.c -> Variable Partitioning - Gets memory partitions and processes as input and returns the processes allocated to each block as output based on first fit, best fit and worst fit
disk.c -> Performs disk scheduling with current head location and the requests given based on FCFS, SSTF, SCAN, C-SCAN, LOOK and C-LOOK