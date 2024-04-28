#ifndef TUTORIAL_TRIANGLE_CPP
#define TUTORIAL_TRIANGLE_CPP

#include "../include/Tutorial_Triangle.h"

#include <vector>
namespace HelperFunctions
{
    void listSupportedInstanceExt() {

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "\nAvailable extensions for Vulkan Instance: \n";

        for (const auto& extension : extensions) { 
            std::cout << "\t" << extension.extensionName << "\n";
        }

    } // end of listSupportedInstanceExt()

} // end of HelperFunctions namespace

void Tutorial_Triangle::run() {

    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();

} // end of run()

void Tutorial_Triangle::initWindow() {
    
    // Create GLFW instance
    glfwInit();
    
    // Window settings before initializing
    
    // Because it was originally made for OpenGL, we tell it to not create a window for that context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Disable window resizing for now -- will come back in the future
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    // Create window and get its reference
    pWindow = glfwCreateWindow(800, 600, "Vulkan Application", nullptr, nullptr);

} // end of initWindow()

void Tutorial_Triangle::initVulkan() {
    createInstance();
} // end of initVulkan()

// Creating the Vulkan Instance
void Tutorial_Triangle::createInstance() {
    
    // Get GLFW info for instance struct creation
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Filling necessary structs to create vulkan instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Application";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    // Create instance
    if(vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    HelperFunctions::listSupportedInstanceExt();

} // end of createInstance()

void Tutorial_Triangle::mainLoop() {
    
    // While window is open
    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();
    }

} // end of mainLoop()

void Tutorial_Triangle::cleanUp() {

    vkDestroyInstance(instance_, nullptr);
    glfwDestroyWindow(pWindow);
    glfwTerminate();

} // end of cleanUp()

#endif // TUTORIAL_TRIANGLE_CPP