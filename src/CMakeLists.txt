find_package(X11 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)


set(INCLUDES  
${CMAKE_SOURCE_DIR}/include/Tutorial_Triangle.h
)

set(SOURCE 
${CMAKE_SOURCE_DIR}/src/VulkanApp.cpp 
${CMAKE_SOURCE_DIR}/src/Tutorial_Triangle.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(VulkanApp ${SOURCE})
#target_include_directories(VulkanApp PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(VulkanApp glfw)
target_link_libraries(VulkanApp glm::glm )
target_link_libraries(VulkanApp Vulkan::Vulkan)

add_custom_target(vulkan-app COMMAND VulkanApp)

