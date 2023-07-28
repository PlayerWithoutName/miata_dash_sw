//
// Created by kaclu on 4/5/2023.
//

#ifndef MIATA_DASH_SW_VULKANSURFACE_H
#define MIATA_DASH_SW_VULKANSURFACE_H
#include "vulkan/vulkan.h"
#include "dependencies/loguru/loguru.hpp"
#include "GLFW/glfw3.h"
#include "VulkanContext.h"

#ifdef __MINGW64__
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "vulkan/vulkan_win32.h"
#else
//TODO: add ARM shit
#endif


class VulkanSurface {
public:
    explicit VulkanSurface(VkInstance);
    ~VulkanSurface();

    void initSurface(GLFWwindow*);
    void createPresentationQueue(VulkanContext*);

    VkSurfaceKHR getKHRSurface();

private:
    VkSurfaceKHR surface{};
    VkInstance instance;

    VkQueue presentationQueue{};
};


#endif //MIATA_DASH_SW_VULKANSURFACE_H
