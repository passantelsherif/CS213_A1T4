#include "Memory.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor to initialize memory with 256 cells, all set to "00"
Memory::Memory() : memory(256, "00") {}

// Get the value stored in a specific memory cell at the given address
std::string Memory::getCell(int address) const {
    return memory[address];
}

// Set the value for a specific memory cell at the given address
void Memory::setCell(int address, const std::string& value) {
    memory[address] = value;
}

// Print memory contents, displaying zeroed cells before the start address
void Memory::printMemory(int startAddress) const {
    cout << "Memory Contents:\n";
    for (int address = startAddress; address < memory.size(); address++) {
        // Print actual memory content starting from startAddress
        cout << setw(2) << setfill('0') << hex << address << ":";
        // Ensure memory has at least 2 characters for each address (or print "00" if shorter)
        cout << setw(2) << setfill('0') << (memory[address].size() >= 2 ? memory[address].substr(0, 2) : "00") << " ";
        // If there’s a second byte, print it for the next address
        if (address + 1 < memory.size()) {
            cout << setw(2) << setfill('0') << hex << (address + 1) << ":";
            cout << setw(2) << setfill('0') << (memory[address].size() >= 4 ? memory[address].substr(2, 2) : "00") << " ";
        }
        // Add a newline after every 8 memory cells for readability
        if ((address - startAddress + 1) % 8 == 0) {
            cout << endl;
        }
    }
    cout << dec << endl; // Switch back to decimal output mode
}