#include <iostream>
#include <vector>
#include "PacketQueue.h"

int main() {
    PacketQueue packets(4, 3);

    unsigned char data1[] = {0x01};
    unsigned char data2[] = {0x00, 0xFF};
    unsigned char data3[] = {0x01, 0x02, 0x03, 0x04};
    unsigned char data4[] = {0x10, 0x20, 0x30, 0x40, 0x50};

    std::cout << "Test 1: Receive packets\n";
    std::cout << packets.receive(1, data1, sizeof(data1)) << '\n';
    std::cout << packets.receive(2, data2, sizeof(data2)) << '\n';
    std::cout << packets.receive(3, data3, sizeof(data3)) << '\n';

    std::cout << "\nTest 2: Queue is full\n";
    std::cout << packets.receive(4, data1, sizeof(data1)) << '\n';

    std::cout << "\nTest 3: Process packets\n";
    int id;
    std::vector<unsigned char> bytes;

    while (packets.processNext(id, bytes)) {
        std::cout << "Processed ID: " << id << '\n';
    }

    std::cout << "\nTest 4: Queue is empty\n";
    std::cout << packets.processNext(id, bytes) << '\n';

    std::cout << "\nTest 5: Reject oversized packet\n";
    std::cout << packets.receive(5, data4, sizeof(data4)) << '\n';

    std::cout << "\nPending packets: " << packets.pending() << '\n';
    std::cout << "Free blocks: " << packets.availableBlocks() << '\n';

    return 0;
}
