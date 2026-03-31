#include "WindowManager.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Callbacks.hpp"

namespace snd3D {

    WindowManager::WindowManager(int width, int height, const char* title, bool enableVsync, Callbacks* callbacksHandler) {
        // Init GLFW
        if (!glfwInit()) {
            throw std::runtime_error("GLFW initialization error");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

        this->window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!this->window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(this->window);
        glfwSwapInterval(enableVsync ? 1 : 0);
        this->vsync = enableVsync;

        // Init GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(this->window);
            glfwTerminate();
            throw std::runtime_error("GLAD initialization error");
        }

        // Init ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL; // Deactivate ini file
        ImGui::StyleColorsDark(); // Set ImGUI dark theme
        ImGui_ImplGlfw_InitForOpenGL(this->window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        // Bind callbacks
        glfwSetWindowUserPointer(this->window, callbacksHandler);
    }

    WindowManager::~WindowManager() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    GLFWwindow* WindowManager::getWindow() {
        return this->window;
    }

    bool WindowManager::isVsyncActive() {
        return this->vsync;
    }

    void WindowManager::toggleVsync() {
        this->vsync = !this->vsync;
        glfwMakeContextCurrent(this->window);
        glfwSwapInterval(this->vsync ? 1 : 0);
    }

    bool WindowManager::isFullScreen() {
        return this->fullScreen;
    }

    void WindowManager::toggleFullScreen() {
        if (this->fullScreen) {
            // Restore last positioning
            glfwSetWindowMonitor(this->window, nullptr, this->lastWindowPosition[0], this->lastWindowPosition[1], this->lastWindowSize[0], this->lastWindowSize[1], GLFW_DONT_CARE);
        } else {
            // Backup old positioning
            glfwGetWindowPos(this->window, &this->lastWindowPosition[0], &this->lastWindowPosition[1]);
            glfwGetWindowSize(this->window, &this->lastWindowSize[0], &this->lastWindowSize[1]);

            // Select the monitor to use as fullscreen and get the size
            GLFWmonitor* currentMonitor = this->getCurrentMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);

            // Switch to full screen
            glfwSetWindowMonitor(this->window, currentMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);

            // Force vsync when enabling fullscreen
            this->vsync = true;
            glfwMakeContextCurrent(this->window);
            glfwSwapInterval(1);
        }
        this->fullScreen = !this->fullScreen;
    }

    GLFWmonitor* WindowManager::getCurrentMonitor() {
        int nmonitors, i;
        int wx, wy, ww, wh;
        int mx, my, mw, mh;
        int overlap, bestoverlap;
        GLFWmonitor* bestmonitor;
        GLFWmonitor** monitors;
        const GLFWvidmode* mode;

        bestoverlap = 0;
        bestmonitor = NULL;

        glfwGetWindowPos(this->window, &wx, &wy);
        glfwGetWindowSize(this->window, &ww, &wh);
        monitors = glfwGetMonitors(&nmonitors);

        for (i = 0; i < nmonitors; i++) {
            mode = glfwGetVideoMode(monitors[i]);
            glfwGetMonitorPos(monitors[i], &mx, &my);
            mw = mode->width;
            mh = mode->height;

            overlap =
                std::max(0, std::min(wx + ww, mx + mw) - std::max(wx, mx)) *
                std::max(0, std::min(wy + wh, my + mh) - std::max(wy, my));

            if (bestoverlap < overlap) {
                bestoverlap = overlap;
                bestmonitor = monitors[i];
            }
        }

        return bestmonitor != NULL ? bestmonitor : glfwGetPrimaryMonitor();
    }
}
