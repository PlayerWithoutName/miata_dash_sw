//
// Created by kaclu on 4/5/2023.
//

#ifndef MIATA_DASH_SW_VULKANSWAPCHAIN_H
#define MIATA_DASH_SW_VULKANSWAPCHAIN_H
#include "vulkan/vulkan.hpp"
#include "GLFW/glfw3.h"
#include "VulkanContext.h"

class VulkanSwapchain {
public:
    explicit VulkanSwapchain(GLFWwindow*, VulkanContext::SwapChainSupportDetails, VkDevice);
    ~VulkanSwapchain();

    void createSwapchain(VkPhysicalDevice, VkSurfaceKHR);
private:
    VkDevice device;

    VkSurfaceFormatKHR surfaceFormat{};
    VkPresentModeKHR presentMode;
    VkExtent2D extent{};

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow*);

    VkSwapchainKHR swapchain{};
    VulkanContext::SwapChainSupportDetails swapchainCapabilities;
};


#endif //MIATA_DASH_SW_VULKANSWAPCHAIN_H
