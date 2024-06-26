#ifndef TUTORIAL_TRIANGLE_H
#define TUTORIAL_TRIANGLE_H

#define GLFW_INCLUDE_VULKAN
// #include <vulkan/vulkan.h> // Not needed for now [14:29 04/28/24]
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <optional>
#include <vector>

namespace HelperSpace
{

    enum IndexType {
        eGraphics     = 0,
        ePresentation = 1
    };

    enum DataTypes {
        eInt    = 0,
        eChar   = 1,
        eBool   = 2,
        eFloat  = 3,
        eDouble = 4,
    };

    // Helper function to obtain correct Queue Families 
    struct QueueFamilyIndices {


        QueueFamilyIndices();
        // ~QueueFamilyIndices(){};

        // Standard functions
        bool isComplete();
        
        // Members
        std::vector<std::optional<uint32_t>> queueFamilyIndices;
    };

    struct QueueFamiliesParams {
        VkPhysicalDevice* physicalDevice;
        VkSurfaceKHR* surface;
    };

    struct SwapChainParams {
        
        VkPhysicalDevice* physicalDevice;
        VkSurfaceKHR* surface;
        VkSurfaceCapabilitiesKHR* capabilities;
        GLFWwindow* window;
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    // Only here for debugging info
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif


    // Just for this scope's purposes
    const std::vector<const char*> sValidationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

} // end of HelperSpace namespace

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

    protected:

    /* Kind of helper functions, will probably move them to the space later. 
     If I start thinking about the design of this code I will get completely off track. 
    */
    void* initParams(const uint8_t paramsType);
    
    // These two functions might only be here until I can think of a design to keep them out
    
    inline HelperSpace::SwapChainParams GetParams(const HelperSpace::SwapChainParams& in);
    inline HelperSpace::QueueFamiliesParams GetParams(const HelperSpace::QueueFamiliesParams& in);

    private:

    // Standard Functions
    void initWindow();
    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void createSwapChain();
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
    VkSwapchainKHR swapChain_;
};

#endif // TUTORIAL_TRIANGLE_H
