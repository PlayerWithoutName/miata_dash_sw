//
// Created by kaclu on 4/5/2023.
//

#include <vector>
#include <set>
#include "VulkanSurface.h"

VulkanSurface::VulkanSurface(VkInstance instance){
    this->instance = instance;
};

VulkanSurface::~VulkanSurface() {
    vkDestroySurfaceKHR(instance, surface, nullptr);
};

void VulkanSurface::initSurface(GLFWwindow *window) {
    VkResult err = glfwCreateWindowSurface(instance, window, nullptr, &surface);
    CHECK_F(err == VK_SUCCESS, "Failed to create Vulkan Surface: %08x", err);
}

void VulkanSurface::createPresentationQueue(VulkanContext *context) {
    VulkanContext::QueueFamilyIndices indices = VulkanContext::findQueueFamilies(context->getPhysicalDevice(), surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }



    vkGetDeviceQueue(context->getDevice(), indices.presentFamily.value(), 0, &presentationQueue);
}

VkSurfaceKHR VulkanSurface::getKHRSurface() {
    return surface;
}