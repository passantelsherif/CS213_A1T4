#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include <string>
#include <limits>
#include "Machine.h"  // Assuming Machine.h exists and includes the necessary Machine class

class MainUI {
private:
    Machine machine;

public:
    void start();  // Main function to start the UI and handle user input
};

#endif  // MAINUI_H
