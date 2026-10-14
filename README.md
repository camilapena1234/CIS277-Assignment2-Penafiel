CIS277 Assignment 2 - Packet Queue
Overview
For this assignment, I added a packet queue to my Assignment 1 code. The queue stores packets and processes them in FIFO (First In, First Out) order, meaning the first packet added is the first one processed.
Files
main.cpp - Runs the program and tests the packet queue.
PacketQueue.h - Contains the packet queue class.
PacketQueue.cpp - Contains the packet queue functions.
MemoryPool.h - Contains the memory pool class.
MemoryPool.cpp - Handles allocating and freeing memory blocks.
Queue.h - Contains the queue implementation.
Stack.h - Contains the stack used by the memory pool.
How It Works
When a packet is received, the program checks if the packet is valid and if there is space available. It then gets a block from the memory pool, copies the packet’s bytes into it, and adds the packet to the queue.
When a packet is processed, the program removes the oldest packet, copies its bytes into the output vector, and returns the memory block to the pool.
The queue and memory pool have different jobs. The queue keeps track of the packets and their order, while the memory pool manages the memory blocks. A memory block cannot be released while its packet is still waiting in the queue.
Testing
The program tests receiving packets, rejecting packets when the queue is full, processing packets in FIFO order, preserving byte values, and checking how many packets and free memory blocks remain.
Time Complexity
Queue operations take O(1) time. Processing a packet takes O(length) time because the bytes have to be copied.
How to Compile and Run
Compile the program with:
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp PacketQueue.cpp MemoryPool.cpp -o main
Run it with:
./main
