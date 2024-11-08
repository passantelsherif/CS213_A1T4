#include "Machine.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "CPU.h"
using namespace std;

Machine::Machine() : programStartAddress(16) {
    // Constructor: initialize program start address and other components
}

void Machine::loadProgram(const string& filename, int startAddress) {
    ifstream file(filename);
    string instruction;
    int address = startAddress;
    programStartAddress = startAddress;  // Set the start address

    if (file.is_open()) {
        while (file >> instruction) {
            memory.setCell(address++, instruction);  // Load instruction into memory
            cout << "Loaded instruction: " << instruction << " into address: " << hex << address - 1 << endl;
        }
        cout << dec << endl;  // Switch back to decimal output mode
        cout << "\nProgram loaded successfully\n" << endl;
        file.close();
    } else {
        cout << "Error: cannot open file\n";
    }
}

void Machine::run() {
    cpu.setProgramCounter(programStartAddress);  // Set the CPU's program counter
    int previousProgramCounter = cpu.getProgramCounter();  // Store the initial program counter

    while (cpu.runningStatus() && cpu.getProgramCounter() < 256) {  // Run the program until halted
        previousProgramCounter = cpu.getProgramCounter();  // Update the previous PC value
        cpu.executeStep(memory);  // Execute a step in the CPU
        cout << "Program Counter: " << cpu.getProgramCounter() << endl;  // Print the PC after each step
    }

    // Print the last valid program counter before halting
    cout << "Program finished executing. Last valid Program Counter: " << previousProgramCounter << "\n";
}

void Machine::displayState(int startAddress) const {
    cout << "Program Counter: " << cpu.getProgramCounter() << "\n";
    cout << endl;
    cpu.displayRegisters();  // Show the register contents
    cout << endl;
    memory.printMemory(startAddress);  // Print memory contents from the start address
    cout << endl;
}
