#ifndef TUTORIAL_TRIANGLE_H
#define TUTORIAL_TRIANGLE_H
#define GLFW_INCLUDE_VULKAN

// #include <vulkan/vulkan.h> // Not needed for now [14:29 04/28/24]
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class Tutorial_Triangle {
    
    public:

    // Functions
    void run();

    private:

    // Functions
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanUp();

    // Members                      // [ 3 Tabs ]
    GLFWwindow* pWindow;             // GLFW window object reference
};
#endif // TUTORIAL_TRIANGLE_H
