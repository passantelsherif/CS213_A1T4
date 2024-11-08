#ifndef REGISTER_H
#define REGISTER_H

#include <vector>
#include <string>

class Register {
private:
    std::vector<std::string> registers;

public:
    Register();
    std::string get(int index) const;
    void set(int index, const std::string& value);

private:
    bool isFloat(const std::string& value) const;
};

#endif // REGISTER_H
