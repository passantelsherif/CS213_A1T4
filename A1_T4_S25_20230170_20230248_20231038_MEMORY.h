#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>

class Memory {
protected:
    std::vector<std::string> memory;
    int size;

public:
    Memory();
    std::string getCell(int address) const;
    void setCell(int address, const std::string& value);
    void printMemory(int startAddress = 0) const;

};

#endif // MEMORY_H
