// ALU.cpp
#include "ALU.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <iostream>

int ALU::hexToDec(const std::string& hex) {
    int value;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> value;
    return value;
}

std::string ALU::decToHex(int value) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << std::hex << (value & 0xFF);
    return ss.str();
}

std::string ALU::add(const std::string& val1, const std::string& val2) {
    int sum = hexToDec(val1) + hexToDec(val2);
    sum = sum & 0xFF;  // Mask to keep only two hexadecimal digits
    return decToHex(sum);
}

std::string ALU::addFloat(const std::string& val1, const std::string& val2) {
    // Convert hexadecimal values to their corresponding float values
    float f1 = hexToFloat(val1);
    float f2 = hexToFloat(val2);

    // Add the two floats
    float sum = f1 + f2;

    // Handle special cases: overflow, NaN, and infinity
    if (std::isinf(sum)) {
        std::cout << "Overflow occurred in floating-point addition. Result set to max float.\n";
        sum = (sum > 0) ? std::numeric_limits<float>::max() : std::numeric_limits<float>::max();
    } else if (std::isnan(sum)) {
        std::cout << "NaN encountered in floating-point addition. Result set to 0.\n";
        sum = 0.0f;
    }

    // Convert the result back to hexadecimal representation
    return floatToHex(sum);
}

float ALU::hexToFloat(const std::string& hex) {
    // Convert hex string to an integer
    int hexInt = hexToDec(hex);

    // Extract sign, exponent, and mantissa
    int sign = (hexInt >> 7) & 0x01;     // 1 bit
    int exponent = (hexInt >> 4) & 0x07; // 3 bits
    int mantissa = hexInt & 0x0F;        // 4 bits

    // Calculate float value based on IEEE 754 8-bit format
    if (exponent == 0 && mantissa == 0) return 0.0f; // Zero case
    float value = 1.0f + (mantissa / 16.0f); // Add the normalized mantissa

    // Adjust value based on exponent
    if (exponent > 0) {
        value *= std::pow(2, exponent - 4); // Exponent bias for 4 bits
    } else {
        value *= std::pow(2, -3); // Underflow for exponent == 0
    }

    // Apply the sign
    return sign ? -value : value;
}

std::string ALU::floatToHex(float f) {
    if (f == 0.0f) return "00"; // Handle zero case

    int sign = f < 0 ? 1 : 0;
    if (sign) f = -f;

    int exponent = 0;
    while (f >= 2.0f) {
        f /= 2.0f;
        exponent++;
    }
    while (f < 1.0f) {
        f *= 2.0f;
        exponent--;
    }

    // Adjust the exponent for bias
    int biasedExponent = exponent + 4; // Bias for 4 bits
    if (biasedExponent <= 0) {
        biasedExponent = 0; // Underflow
    } else if (biasedExponent >= 7) {
        biasedExponent = 7; // Overflow
    }

    int mantissa = static_cast<int>((f - 1.0f) * 16.0f) & 0x0F; // Keep 4 bits
    int hexInt = (sign << 7) | (biasedExponent << 4) | mantissa;

    return decToHex(hexInt);
}
