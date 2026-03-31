#pragma once

#define GLFW_INCLUDE_NONE // Include only GLFW types
#include "GLFW/glfw3.h"

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

        private:
            GLFWwindow* window;
            bool vsync, fullScreen = false;
            int lastWindowPosition[2] = {0, 0}, lastWindowSize[2] = {0, 0}; // Used to toggle between full screen and windowed view

            GLFWmonitor* getCurrentMonitor();
    };
}
