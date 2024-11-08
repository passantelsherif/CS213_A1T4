#include "MainUI.h"

void MainUI::start() {
    int choice;
    while (true) {
        std::cout << "1. Load program from file\n"
                  << "2. Execute program\n"
                  << "3. Display state\n"
                  << "4. Exit program\n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input
            std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "Enter file name with the extension:" << std::endl;
            std::string filename;
            std::cin >> filename;

            int startAddress;
            std::string startAddressHex;
            std::cout <<  "Enter starting memory address in hexadecimal only (or press 10 for default): ";
            std::cin >> startAddressHex;
            startAddress = std::stoi(startAddressHex, nullptr, 16);

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                startAddress = 16;
            }

            machine.loadProgram(filename, startAddress);

        } else if (choice == 2) {
            machine.run();
        } else if (choice == 3) {
            machine.displayState();
        } else if (choice == 4) {
            std::cout << "Thanks for using the program\n";
            break;
        } else {
            std::cout << "Invalid input. Please choose 1, 2, 3, or 4\n";
        }
    }
}

