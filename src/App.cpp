#include "App.hpp"

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Constants.hpp"
#include "Callbacks.hpp"

namespace snd3D {

    App::App() {

        this->windowManager = std::make_unique<WindowManager>(
            snd3D::constants::window::DEFAULT_WIDTH,
            snd3D::constants::window::DEFAULT_HEIGHT,
            snd3D::constants::window::NAME,
            snd3D::constants::window::DEFAULT_VSYNC,
            new Callbacks(*this)
        );

        this->scene = std::make_unique<Scene>(*this->windowManager);
    }

    void App::run() {

        // Game Loop
        while (!glfwWindowShouldClose(this->windowManager->getWindow())) {
            glfwPollEvents();

            this->scene->update();

            // Start ImGui Frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Info");
            ImGui::Text("Hello from ImGui!");
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::End();

            // Rendering
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            scene->render();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(this->windowManager->getWindow());
        }
    }
}