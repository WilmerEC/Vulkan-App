#ifndef TUTORIAL_TRIANGLE_CPP
#define TUTORIAL_TRIANGLE_CPP

#include "Tutorial_Triangle.h"

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

} // end of initVulkan()

void Tutorial_Triangle::mainLoop() {
    
    // While window is open
    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();
    }

} // end of mainLoop()

void Tutorial_Triangle::cleanUp() {

    glfwDestroyWindow(pWindow);
    glfwTerminate();

} // end of cleanUp()

#endif // TUTORIAL_TRIANGLE_CPP