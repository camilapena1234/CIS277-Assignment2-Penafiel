#include <iostream>
#include <vector>
#include "PacketQueue.h"

int main() {
    PacketQueue packets(8, 3);

    unsigned char data1[] = {0x01, 0x00, 0xFF};
    unsigned char data2[] = {0x02, 0x10, 0x20};
    unsigned char data3[] = {0x03, 0x30, 0x40};

    std::cout << "Initial free blocks: "
              << packets.availableBlocks() << '\n';

    std::cout << "Receive packet 1: "
              << packets.receive(1, data1, sizeof(data1)) << '\n';

    std::cout << "Receive packet 2: "
              << packets.receive(2, data2, sizeof(data2)) << '\n';

    std::cout << "Receive packet 3: "
              << packets.receive(3, data3, sizeof(data3)) << '\n';

    std::cout << "Receive when full: "
              << packets.receive(4, data1, sizeof(data1)) << '\n';

    std::cout << "Packets waiting: "
              << packets.pending() << '\n';

    int id;
    std::vector<unsigned char> bytes;

    if (packets.processNext(id, bytes)) {
        std::cout << "Processed packet ID: " << id << '\n';
        std::cout << "Bytes: ";

        for (unsigned char byte : bytes) {
            std::cout << "0x" << std::hex
                      << static_cast<int>(byte) << ' ';
        }

        std::cout << std::dec << '\n';
    }

    std::cout << "Free blocks after processing: "
              << packets.availableBlocks() << '\n';

    std::cout << "Receive packet 4 after processing: "
              << packets.receive(4, data1, sizeof(data1)) << '\n';

    while (packets.processNext(id, bytes)) {
        std::cout << "Processed packet ID: " << id << '\n';
    }

    std::cout << "Packets waiting at end: "
              << packets.pending() << '\n';

    return 0;
}

