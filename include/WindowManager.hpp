#pragma once

#define GLFW_INCLUDE_NONE // Include only GLFW data types
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Callbacks.hpp"

namespace snd3D {
    class WindowManager {
        public:
            WindowManager(int width, int height, const char* title, bool enableVsync, Callbacks* callbacksHandler);
            ~WindowManager();
            GLFWwindow* getWindow();
            bool isVsyncActive();
            void toggleVsync();
            bool isFullScreen();
            void toggleFullScreen();
            void frameBufferChanged();
            bool isFramebufferChanged();
            glm::vec2 getCurrentResolution();
            float getAspectRatio();

        private:
            GLFWwindow* window;
            bool framebufferChanged, vsync, fullScreen = false;
            int lastWindowPosition[2] = {0, 0}, lastWindowSize[2] = {0, 0}; // Used to toggle between full screen and windowed view

            GLFWmonitor* getCurrentMonitor();
    };
}
