//
// Created by kaclu on 4/4/2023.
//

#ifndef MIATA_DASH_SW_GRAPHICS_H
#define MIATA_DASH_SW_GRAPHICS_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "VulkanContext.h"

class Graphics {


public:
    Graphics();
    ~Graphics();

    void initDisplay();
    bool shouldClose();
    void tick(double delta);

    GLFWwindow* getWindow();

private:
    GLFWwindow *window{};
    VulkanContext *vulkanContext{};

    static void checkGLFWError(int err);
    static void checkVulkanAvailable();
    void createWindow();
    void destroyWindow();
};


#endif //MIATA_DASH_SW_GRAPHICS_H
