set( SOURCE VulkanApplication.cpp )
link_directories($CMAKE_CURRENT_SOURCE_DIR/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(VulkanApp SOURCE)
