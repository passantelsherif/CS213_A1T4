#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include "Register.h"  // Assuming Register.h exists
#include "CU.h"        // Assuming CU.h exists
#include "Memory.h"    // Assuming Memory.h exists

class CPU {
private:
    int programCounter;
    Register reg;
    CU cu;
    bool isRunning;  // Flag to check if CPU is running

public:
    CPU();  // Constructor

    void setProgramCounter(int address);  // Set program counter address
    void executeStep(Memory& mem);  // Execute one step
    void displayRegisters() const;  // Display all register values
    int getProgramCounter() const;  // Get current program counter value
    bool runningStatus() const;  // Check if CPU is running

private:
    int hexToDec(char hexChar) const;  // Helper function to convert hex to decimal
};

#endif  // CPU_H
