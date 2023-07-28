//
// Created by kaclu on 4/5/2023.
//

#include "VulkanSwapchain.h"
#include "dependencies/loguru/loguru.hpp"
#include <limits>
#include <algorithm>

VulkanSwapchain::VulkanSwapchain(GLFWwindow* window, VulkanContext::SwapChainSupportDetails swapChainSupportDetails, VkDevice device) {
    this->device = device;

    swapchainCapabilities = swapChainSupportDetails;

    surfaceFormat = chooseSwapSurfaceFormat(swapChainSupportDetails.formats);
    presentMode = chooseSwapPresentMode(swapChainSupportDetails.presentModes);
    extent = chooseSwapExtent(swapChainSupportDetails.capabilities, window);
}

VulkanSwapchain::~VulkanSwapchain() {
    vkDestroySwapchainKHR(device, swapchain, nullptr);
}

VkSurfaceFormatKHR VulkanSwapchain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR VulkanSwapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void VulkanSwapchain::createSwapchain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount = swapchainCapabilities.capabilities.minImageCount + 1 < swapchainCapabilities.capabilities.maxImageCount?
            swapchainCapabilities.capabilities.minImageCount + 1:
            swapchainCapabilities.capabilities.minImageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    VulkanContext::QueueFamilyIndices indices = VulkanContext::findQueueFamilies(physicalDevice, surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }


    createInfo.preTransform = swapchainCapabilities.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;


    VkResult err = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
    CHECK_F(err == VK_SUCCESS, "Error creating the swapchain: %08x", err);
    LOG_F(INFO, "beniz");
}
