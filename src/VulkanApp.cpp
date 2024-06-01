

// Project Includes first
#include "Tutorial_Triangle.h"

// Global Includes after
#include <iostream>

int main(int argc, char** argv)
{

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


