#include "CU.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Execute an instruction and modify the program counter and registers accordingly
bool CU::executeInstruction(const std::string& instruction, int& pc, Register& reg, Memory& mem) {
    char opcode = instruction[0];
    int regIdx = hexToDec(instruction[1]); // Register index
    int operand1 = hexToDec(instruction[2]);
    int operand2 = hexToDec(instruction[3]);

    cout << "Executing instruction: " << instruction << " at PC: " << pc << endl;

    switch (opcode) {
        case '1':  // LOAD RXY
            reg.set(regIdx, mem.getCell(operand1 * 16 + operand2));
            break;
        case '2':  // LOAD immediate RXY
            // Load immediate value into register
            reg.set(regIdx, instruction.substr(2, 2));
            cout << "Loaded immediate value into R" << regIdx << ": " << reg.get(regIdx) << endl;
            break;
        case '3':  // STORE RX to memory address XY
            mem.setCell(operand1 * 16 + operand2, reg.get(regIdx));

        //Check if XY = 00 to display Screen
        if(to_string(operand1)+to_string(operand2) == "00"){
            cout<< "Screen in ASCII: " << char(stoi(reg.get(regIdx), nullptr, 16)) <<endl;
            cout<< "Screen in Hexadecimal: " <<reg.get(regIdx) <<endl;
        }
        break;
        case '4':  // MOVE R to S
            reg.set(operand2, reg.get(operand1));
            break;
        case '5':  // ADD S and T, store in R
            reg.set(regIdx, alu.add(reg.get(operand1), reg.get(operand2)));
            cout << "Added R" << operand1 << " and R" << operand2 << " to R" << regIdx << ": " << reg.get(regIdx) << endl;
            break;
        case '6':  // ADD floating-point S and T, store in R
            reg.set(regIdx, alu.addFloat(reg.get(operand1), reg.get(operand2)));
            cout << "Added float R" << operand1 << " and R" << operand2 << " to R" << regIdx << ": " << reg.get(regIdx) << endl;
            break;
        case 'B':  // JUMP to address XY if R equals R0
            if (reg.get(regIdx) == reg.get(0)) {
                pc = operand1 * 16 + operand2; // Jump to specified address
                return true;  // Jump occurred, do not increment PC
            }
            break;
        case 'C':  // HALT
            cout << "Program halted.\n";
            return false;  // Signal to halt
        default:
            cout << "Invalid instruction: " << instruction << "\n";
            return false;  // Signal to halt
    }
    return true;  // Continue running
}

// Convert a hexadecimal character to its decimal equivalent
int CU::hexToDec(char hexChar) {
    return (hexChar >= '0' && hexChar <= '9') ? hexChar - '0' : hexChar - 'A' + 10;
}
