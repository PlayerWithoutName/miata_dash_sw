#include <iostream>
#include "Graphics.h"
#include "Timer.h"
#include "dependencies/loguru/loguru.hpp"
#include "VulkanSurface.h"
#include "VulkanSwapchain.h"

int main(int argc, char** argv) {
    loguru::init(argc, argv);

    auto *graphics = new Graphics();
    graphics->initDisplay();
    LOG_F(INFO, "Display Init Complete");

    auto *context = new VulkanContext();
    LOG_F(INFO, "Context Init Complete");

    auto *surface = new VulkanSurface(context->getInstance());
    surface->initSurface(graphics->getWindow());
    LOG_F(INFO, "Surface Init Complete");

    context->pickDevice(surface->getKHRSurface());
    context->initLogicalDevice(surface->getKHRSurface());

    context->createQueue(surface->getKHRSurface());
    surface->createPresentationQueue(context);
    LOG_F(INFO, "Surface Presentation Queue Complete");


    auto *swapchain = new VulkanSwapchain(graphics->getWindow(),
                                          VulkanContext::querySwapChainSupport(context->getPhysicalDevice(), surface->getKHRSurface()),
                                          context->getDevice());
    LOG_F(INFO, "Swapchain Init Complete");
    swapchain->createSwapchain(context->getPhysicalDevice(), surface->getKHRSurface());

    auto *frameTimer = new Timer;

    while(!graphics->shouldClose()){
        graphics->tick(frameTimer->lap());
        break;
    }

    delete swapchain;
    delete surface;
    delete frameTimer;
    delete context;
    delete graphics;
}
