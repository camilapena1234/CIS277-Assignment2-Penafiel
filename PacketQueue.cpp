#include "PacketQueue.h"

PacketQueue::PacketQueue(std::size_t blockSize, std::size_t blockCount)
    : pool_(blockSize, blockCount), queue_(blockCount) {
}

bool PacketQueue::receive(std::size_t id, const unsigned char* bytes,
                          std::size_t length) {
    if (bytes == nullptr || length == 0 ||
        length > pool_.blockSize() || queue_.full()) {
        return false;
    }

    void* block = pool_.allocate();

    if (block == nullptr) {
        return false;
    }

    unsigned char* destination = static_cast<unsigned char*>(block);

    for (std::size_t i = 0; i < length; ++i) {
        destination[i] = bytes[i];
    }

    PacketDescriptor packet = {id, block, length};

    if (!queue_.enqueue(packet)) {
        pool_.deallocate(block);
        return false;
    }

    return true;
}

bool PacketQueue::processNext(std::size_t& id, std::vector<unsigned char>& bytes) {
    PacketDescriptor packet;

    if (!queue_.dequeue(packet)) {
        return false;
    }

    id = static_cast<int>(packet.id);

    const unsigned char* source =
        static_cast<const unsigned char*>(packet.block);

    bytes.assign(source, source + packet.length);

    pool_.deallocate(packet.block);

    return true;
}

std::size_t PacketQueue::pending() const {
    return queue_.size();
}

std::size_t PacketQueue::availableBlocks() const {
    return pool_.availableBlocks();
}
