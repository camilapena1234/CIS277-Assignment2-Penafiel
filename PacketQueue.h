#ifndef PACKETQUEUE_H
#define PACKETQUEUE_H

#include <cstddef>
#include <vector>
#include "MemoryPool.h"
#include "Queue.h"
#include "PacketQueue.h"

class PacketQueue {
private:
    struct PacketDescriptor {
        std::size_t id;
        void* block;
        std::size_t length;
    };

    MemoryPool pool_;
    Queue<PacketDescriptor> queue_;

public:
    PacketQueue(std::size_t blockSize, std::size_t blockCount);

    bool receive(std::size_t id, const unsigned char* bytes,
                 std::size_t length);

    bool processNext(int& id, std::vector<unsigned char>& bytes);

    std::size_t pending() const;

    std::size_t availableBlocks() const;
};

#endif


