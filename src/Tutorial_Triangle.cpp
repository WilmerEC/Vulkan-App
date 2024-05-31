

#include "Tutorial_Triangle.h"

#include <cstring>
#include <optional>

namespace HelperSpace
{

    void logPauseSingle(const char* name, void* data, DataTypes dataType, bool pause) {
        
        switch (dataType) {
            
            case DataTypes::eInt: 
            {
                std::cout << "\n" << name << ": " << *(static_cast<int*>(data)); 
                if (pause) { std::cin.get(); }
            } break;

            case DataTypes::eChar: 
            {
                std::cout << "\n" << name << ": " << *(static_cast<char*>(data)); 
                if (pause) { std::cin.get(); }
            } break;

            case DataTypes::eBool: 
            {
                std::cout << "\n" << name << ": " << *(static_cast<bool*>(data)); 
                if (pause) { std::cin.get(); }
            } break;

            case DataTypes::eFloat: 
            {
                std::cout << "\n" << name << ": " << *(static_cast<float*>(data)); 
                if (pause) { std::cin.get(); }
            } break;

            case DataTypes::eDouble: 
            {
                std::cout << "\n" << name << ": " << *(static_cast<double*>(data)); 
                if (pause) { std::cin.get(); }
            } break;

            default:
            break;
        }
        std::cout << "\n";
    }

    void logPauseChunk(std::vector<const char*> names, std::vector<void*> data, std::vector<DataTypes> dataTypes) {
        
        std::cout << "\n";

        for (int i = 0; i < names.size(); i++) {
            logPauseSingle(names[i], data[i], dataTypes[i], false);
        }
        
        std::cin.get();
    }

    // Helper function to obtain correct Queue Families 
    QueueFamilyIndices::QueueFamilyIndices() {
        
        queueFamilyIndices = {};

        /* 
         *   We're only querying for 2 kinds of queue families. 
         *   TO-DO: Make constant(s) of queue families needed to be queried 
         *   and replace int literal by that variable
        */
        for (int i = 0; i < 2; i++) {
            std::optional<uint32_t> temp;
            queueFamilyIndices.push_back(temp);
        }
        
    }

    bool QueueFamilyIndices::isComplete() {
        return queueFamilyIndices[ HelperSpace::eGraphics].has_value() && queueFamilyIndices[HelperSpace::ePresentation].has_value();
    }
    
    // Helper function that lists all the supported instance extensions 
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

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : sValidationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                layerFound = (strcmp(layerName, layerProperties.layerName) == 0) ? true : false;
                break;
            }

            if (!layerFound && enableValidationLayers) {
                
                throw std::runtime_error("Validation layers requested, but not available!");
            }
        }

        return true;

    } // end of checkValidationLayersSupport()

    QueueFamilyIndices findQueueFamilies(const HelperSpace::QueueFamiliesParams param) {
        QueueFamilyIndices indices;

        // Retrieve number of queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(*param.physicalDevice, &queueFamilyCount, nullptr);

        // Create vector that will contain all queue families available in this GPU
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        // Retrieve all queue families available in this GPU
        vkGetPhysicalDeviceQueueFamilyProperties(*param.physicalDevice, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        VkBool32 presentSupport = false;
        for (const auto& queueFamily : queueFamilies) {
            
            // Adding graphics queue family into the indices struct
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.queueFamilyIndices[HelperSpace::eGraphics] = i;
            }

            // Adding presentation queue family into indices struct
            vkGetPhysicalDeviceSurfaceSupportKHR(*param.physicalDevice, i, *param.surface, &presentSupport);
            
            if (presentSupport == true ) {
                indices.queueFamilyIndices[HelperSpace::ePresentation] = i;
            }
            
            if(indices.queueFamilyIndices[eGraphics].value() == indices.queueFamilyIndices[ePresentation].value()) {
                break;
            }

            i++;
        }
        
        return indices;

    } // end of findQueueFamilies()

    int rateDeviceSuitability(const HelperSpace::QueueFamiliesParams param) {
        
        // Check for GPU properties and features
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;

        QueueFamilyIndices indices = findQueueFamilies(param);

        vkGetPhysicalDeviceProperties(*param.physicalDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(*param.physicalDevice, &deviceFeatures);

        int score = (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) ? (score + 1000) : 
                    ((deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) ? 10000 : 0);

        std::cout << "\nVK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: " << VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU <<
                     "\nVK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: " << VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU << 
                     "\ndeviceProperties.deviceType: " << deviceProperties.deviceType <<
                     "\ndeviceProperties.limits.maxImageDimension2D: " << deviceProperties.limits.maxImageDimension2D << std::endl;

        if ((score >= 1000) && (score < 1500)) {
            std::cout << "\nGPU Type: DISCRETE (score: " << score << ")" << "\n";
        } else if (score >= 10000 && score <= 10500) {
            std::cout << "\nGPU Type: INTEGRATED (score: " << score << ")" << "\n";
        } else {
            std::cout << "\nGPU Type: UNKNOWN (score: " << score << ")" << "\n";
        }

        score += deviceProperties.limits.maxImageDimension2D;
        
        return ( ( !deviceFeatures.geometryShader ) && ( !indices.isComplete() ) ) ? 0 : score;
    }

    std::vector<VkDeviceQueueCreateInfo> getQueueInfos( HelperSpace::QueueFamilyIndices indices, HelperSpace::QueueFamiliesParams param ) 
    {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        float queuePriorities[1] = {1.0f};

        for(int i = 0; i < indices.queueFamilyIndices.size(); i++)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = indices.queueFamilyIndices[i].value();
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriorities[0];
            queueCreateInfos.push_back(queueCreateInfo);

            if(indices.queueFamilyIndices[eGraphics].value() == indices.queueFamilyIndices[ePresentation].value()) {
                break;
            }
        }
        return queueCreateInfos;
    }

} // end of HelperSpace namespace

//////// Standard Functions

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
    pWindow_ = glfwCreateWindow(800, 600, "Vulkan Application", nullptr, nullptr);

} // end of initWindow()

void Tutorial_Triangle::initVulkan() {
    
    createInstance();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();

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
    createInfo.enabledLayerCount = enableValidationLayers ? static_cast<uint32_t>(validationLayers.size()) : 0;
    createInfo.ppEnabledLayerNames = enableValidationLayers ? validationLayers.data() : nullptr;

    // Create instance
    if(vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    HelperSpace::listSupportedInstanceExt();

} // end of createInstance()

// Search and select appropriate GPU
void Tutorial_Triangle::pickPhysicalDevice() {

    // First we have to list all the GPUs available
    uint32_t deviceCount = 0;

    // Get the number of GPUs detected
    vkEnumeratePhysicalDevices(instance_, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance_, &deviceCount, devices.data());
    HelperSpace::QueueFamiliesParams param;
    param.surface = &surface_;

    for (auto& device : devices) {
        param.physicalDevice = &device;
        physicalDevice_ = HelperSpace::rateDeviceSuitability(param) >= 1000 ? device : VK_NULL_HANDLE;
        break;
    }

    if (physicalDevice_ == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }

} // end of pickPhysicalDevice()

void Tutorial_Triangle::createLogicalDevice() {

    HelperSpace::QueueFamiliesParams param;
    param.physicalDevice = &physicalDevice_;
    param.surface = &surface_;    

    // Get the queue family indices based on our requirements
    HelperSpace::QueueFamilyIndices indices = HelperSpace::findQueueFamilies(param);
    
    // First step in creating a device is filling it with the queues info.
    // Get the necessary amount of queue create infos to avoid duplication of queues and save resources & performance
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = HelperSpace::getQueueInfos(indices, param);

    // Next step is to gather all the device features
    VkPhysicalDeviceFeatures deviceFeatures{}; // will use later, needed to create device

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;

    // This is only needed for older implementations
    createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice_, &createInfo, nullptr, &device_) != VK_SUCCESS) {
        throw std::runtime_error("\nFailed to create Logical Device!");
    }

    // Get queue and store it in its handle
    vkGetDeviceQueue(device_, indices.queueFamilyIndices[HelperSpace::eGraphics].value(), 0, &graphicsQueue_);
    vkGetDeviceQueue(device_, indices.queueFamilyIndices[HelperSpace::ePresentation].value(), 0, &presentQueue_);

} // end of createLogicalDevice()

void Tutorial_Triangle::createSurface() 
{
    if (glfwCreateWindowSurface(instance_, pWindow_, nullptr, &surface_) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Tutorial_Triangle::mainLoop() 
{
    
    // While window is open
    while (!glfwWindowShouldClose(pWindow_))
    {
        glfwPollEvents();
    }

} // end of mainLoop()

void Tutorial_Triangle::cleanUp() 
{

    vkDestroyDevice(device_, nullptr);
    vkDestroySurfaceKHR(instance_, surface_, nullptr);
    vkDestroyInstance(instance_, nullptr);
    glfwDestroyWindow(pWindow_);
    glfwTerminate();

} // end of cleanUp()

