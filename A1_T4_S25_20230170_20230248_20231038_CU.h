#ifndef CU_H
#define CU_H

#include <string>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"

class CU {
private:
    ALU alu;

public:
    bool executeInstruction(const std::string& instruction, int& pc, Register& reg, Memory& mem);
    int hexToDec(char hexChar);
};

#endif // CU_H
