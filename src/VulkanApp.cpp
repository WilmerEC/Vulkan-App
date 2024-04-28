#ifndef VULKANAPP_CPP
#define VULKANAPP_CPP

#include "../include/Tutorial_Triangle.h"

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

#endif // VULKANAPP_CPP
