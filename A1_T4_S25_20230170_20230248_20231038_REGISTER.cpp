#include "Register.h"
#include <string>

// Constructor to initialize registers with "0000" values
Register::Register() : registers(16, "0000") {}

// Get the value of a register at a specific index
std::string Register::get(int index) const {
    return registers[index];
}

// Set the value of a register at a specific index
void Register::set(int index, const std::string& value) {
    registers[index] = (value.length() > 2) ? value.substr(value.length() - 2, 2) : value;
}

// Helper function to check if a value represents a float
bool Register::isFloat(const std::string& value) const {
    // Placeholder logic to check if a value is a float
    return value != "0000" && value != "0001";  // Customize based on specific criteria
}

