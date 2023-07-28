//
// Created by kaclu on 4/4/2023.
//

#include <cstring>
#include <thread>
#include "Graphics.h"

#include "dependencies/loguru/loguru.hpp"

//#define MONITOR
#define MONITOR_W 800
#define MONITOR_H 800

#define DISP_FPS

Graphics::Graphics() {
    checkGLFWError(glfwInit());
    checkVulkanAvailable();
}

Graphics::~Graphics() {
    destroyWindow();
    glfwTerminate();
}

void Graphics::initDisplay() {
    createWindow();
}

void Graphics::checkGLFWError(int err) {
    CHECK_F(err == GLFW_TRUE, "GLFW ERROR: %08x", err);
}

void Graphics::checkVulkanAvailable() {
    CHECK_F(glfwVulkanSupported(), "Vulkan is not supported!");
}

void Graphics::createWindow() {
    GLFWmonitor* monitor = nullptr;

#ifdef MONITOR
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    for(int i = 0; i<count; ++i){
        const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);

        if(mode->width == MONITOR_W && mode->height == MONITOR_H){
            monitor = monitors[i];
        }
    }
#endif

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(800, 800, "Miata", monitor, nullptr);
}

void Graphics::destroyWindow() {
    glfwDestroyWindow(window);
}

bool Graphics::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Graphics::tick(double delta) {
#ifdef DISP_FPS
    LOG_F(INFO, "FPS: %.3f", 1.0/delta);
#endif

    glfwPollEvents();
}

GLFWwindow *Graphics::getWindow() {
    return window;
}

