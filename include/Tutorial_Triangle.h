#ifndef TUTORIAL_TRIANGLE_H
#define TUTORIAL_TRIANGLE_H

#define GLFW_INCLUDE_VULKAN
// #include <vulkan/vulkan.h> // Not needed for now [14:29 04/28/24]
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class Tutorial_Triangle {
    
    public:

    // Functions
    void run();

    // Members
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

    // Just here for debugging info
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    private:

    // Functions
    void initWindow();
    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void mainLoop();
    void cleanUp();

    // Members                                                   // [ 10 Tabs ]
    GLFWwindow* pWindow_;                                        // GLFW window object reference
    VkInstance instance_;                                        // Vulkan instance
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;           // Selected GPU handle
    VkDevice device_;                                            // Logical device that interfaces with the physical device
    VkQueue graphicsQueue_;                                      // Graphcic queues interface handle
    VkQueue presentQueue_;                                       // Presentation queues interface handle
    VkSurfaceKHR surface_;                                       // Platform agnostic windows surface handle
};

#endif // TUTORIAL_TRIANGLE_H
#include "../src/Tutorial_Triangle.cpp"
