// ALU.h
#ifndef ALU_H
#define ALU_H

#include <string>
using namespace std;
class ALU {
public:
    int hexToDec(const std::string& hex);
    string decToHex(int value);
    string add(const std::string& val1, const std::string& val2);
    string addFloat(const std::string& val1, const std::string& val2);

private:
    float hexToFloat(const std::string& hex);
    string floatToHex(float f);
};

#endif
