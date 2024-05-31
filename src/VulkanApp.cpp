

// Project Includes first
#include "Tutorial_Triangle.h"

// Global Includes after
#include <iostream>

int main(int argc, char** argv)
{
    // Test

    uint8_t temp1 = 5;
    uint8_t temp2 = 4;
    uint8_t result = temp1 & temp2;
    // std::cout <<  "\ntemp1: 0x" << std::hex << temp1 << "\ntemp2: 0x" << std::hex << temp2 << "\nresult: "  << (temp1 & temp2);
    std::cout << "\nLuis es marico"; // Easter Egg

    Tutorial_Triangle app;

    try {
        app.run();
    } 
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}


