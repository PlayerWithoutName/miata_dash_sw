cmake_minimum_required(VERSION 3.25)
project(miata_dash_sw)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/include)
link_libraries(${PROJECT_SOURCE_DIR}/dependencies/glfw/lib/libglfw3.a)



set(ENV{VULKAN_SDK} "C:/VulkanSDK/1.3.243.0")
find_package(Vulkan REQUIRED)
link_libraries(${Vulkan_LIBRARIES})
include_directories(PUBLIC "C:/VulkanSDK/1.3.243.0/Include")

add_executable(miata_dash_sw main.cpp Graphics.cpp Graphics.h VulkanContext.cpp VulkanContext.h Resources.cpp Resources.h Timer.cpp Timer.h dependencies/loguru/loguru.cpp dependencies/loguru/loguru.hpp VulkanSurface.cpp VulkanSurface.h VulkanSwapchain.cpp VulkanSwapchain.h)
