#ifndef MACHINE_H
#define MACHINE_H
#include "CPU.h"
#include "CPU.h"
#include "Memory.h"

class Machine {
private:
    CPU cpu;  // The CPU component
    Memory memory;  // The memory component
    int programStartAddress;

public:
    Machine();  // Constructor
    void loadProgram(const std::string& filename, int startAddress = 16);  // Load program into memory
    void run();  // Run the program
    void displayState(int startAddress = 0) const;  // Display the current state of the machine
};

#endif // MACHINE_H
