#include "CPU.h"

CPU::CPU() : programCounter(0), isRunning(true) {}

void CPU::setProgramCounter(int address) {
    programCounter = address;
}

void CPU::executeStep(Memory& mem) {
    if (!isRunning) return;  // Halted state

    // Fetch the instruction from memory
    std::string instruction = mem.getCell(programCounter);
    std::cout << "Fetched instruction: " << instruction << " at PC: " << programCounter << std::endl;

    // Check for invalid or empty instruction
    if (instruction == "0000" || instruction.empty()) {
        std::cout << "Invalid or empty instruction encountered. Halting execution.\n";
        isRunning = false;  // Halt the program
        return;
    }

    // Execute the instruction and check if we should update the program counter
    isRunning = cu.executeInstruction(instruction, programCounter, reg, mem);

    if (isRunning) {
        // Increment PC only if no jump occurred
        if (!(instruction[0] == 'B' && reg.get(hexToDec(instruction[1])) == reg.get(0))) {
            programCounter++;
        }
    }
}

void CPU::displayRegisters() const {
    for (int i = 0; i < 16; ++i) {
        std::cout << "R" << i << ": " << reg.get(i) << std::endl;
    }
    std::cout << "\n";
}

int CPU::getProgramCounter() const {
    return programCounter;
}

bool CPU::runningStatus() const {
    return isRunning;  // Return running status
}

int CPU::hexToDec(char hexChar) const {
    return (hexChar >= '0' && hexChar <= '9') ? hexChar - '0' : hexChar - 'A' + 10;
}
