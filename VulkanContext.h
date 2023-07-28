//
// Created by kaclu on 4/4/2023.
//

#ifndef MIATA_DASH_SW_VULKANCONTEXT_H
#define MIATA_DASH_SW_VULKANCONTEXT_H

#include <optional>
#include <vector>
#include "vulkan/vulkan.h"

class VulkanContext {
public:
    VulkanContext();
    ~VulkanContext();

    void pickDevice(VkSurfaceKHR surface);
    void initLogicalDevice(VkSurfaceKHR surface);
    void createQueue(VkSurfaceKHR surface);

    VkInstance getInstance();
    VkPhysicalDevice getPhysicalDevice();


    VkDevice getDevice();

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
    };
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice, VkSurfaceKHR);

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
private:



    void createInstance();
    void registerDebugMessenger();

    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};

    VkPhysicalDevice physicalDevice{};
    VkDevice device{};

    VkQueue graphicsQueue{};

    static VkBool32 debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);

    static bool isDeviceSuitable(VkPhysicalDevice const &device, VkSurfaceKHR surface);
};


#endif //MIATA_DASH_SW_VULKANCONTEXT_H
