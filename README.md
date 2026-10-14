# CIS-277 Assignment 2: Network Packet Arrival Queue

## Student

This assignment adds a packet queue to my Assignment 1 code.

## Design

The queue stores packets and processes them in FIFO (First In, First Out) order. The first packet added is the first one processed.

The main files are:

- `main.cpp` - Runs the program and tests the packet queue.
- `PacketQueue.h` - Contains the packet queue class.
- `PacketQueue.cpp` - Contains the packet queue functions.
- `MemoryPool.h` - Contains the memory pool class.
- `MemoryPool.cpp` - Handles allocating and freeing memory blocks.
- `Queue.h` - Contains the queue implementation.
- `Stack.h` - Contains the stack used by the memory pool.

When a packet is received, the program checks if it is valid and if there is space available. It gets a block from the memory pool, copies the packet bytes into it, and adds the packet to the queue.

When a packet is processed, the program removes the oldest packet, copies its bytes into the output vector, and returns the memory block to the pool.

## How to Compile

Compile the program with:

    g++ -std=c++23 -Wall -Wextra -pedantic main.cpp PacketQueue.cpp MemoryPool.cpp -o main

## How to Run

On Windows, run:

    .\main.exe

## Tests and Results

The program tests receiving packets, rejecting packets when the queue is full, and processing packets in FIFO order. It also checks packet byte values and memory block reuse.

## Analysis Questions

Queue operations take O(1) time for basic enqueue and dequeue operations. Copying a packet takes O(length) time because its bytes must be copied.

FIFO means the first packet received is the first packet processed. LIFO means the last item added is the first item removed. This queue uses FIFO.

The memory pool reuses memory blocks instead of allocating new memory for every packet.

## AI Use

I used AI to help understand the assignment instructions and organize the README. I reviewed the content to make sure it describes my project.
