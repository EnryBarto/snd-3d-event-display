#include "App.hpp"

#include <iostream>

#include <glad/glad.h>

#include "Constants.hpp"
#include "Callbacks.hpp"

namespace snd3D {

    App::App() {
        this->windowManager = std::make_unique<WindowManager>(
            snd3D::constants::defaults::window::WIDTH,
            snd3D::constants::defaults::window::HEIGHT,
            snd3D::constants::defaults::window::NAME,
            snd3D::constants::defaults::window::VSYNC,
            new Callbacks(*this)
        );
        this->guiManager = std::make_unique<Gui>(*this, constants::sizes::GUI_FONT);
        this->scene = std::make_unique<Scene>(*this->windowManager, this->stateManager, this->settings);
    }

    void App::run() {

        // Game Loop
        while (this->stateManager.getCurrentState() != AppState::CLOSED) {
            glfwPollEvents();
            if (glfwWindowShouldClose(this->windowManager->getWindow())) this->stateManager.close();

            this->stateManager.update();
            this->scene->update();
            this->guiManager->update();

            // Rendering
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->scene->render();
            this->guiManager->render();

            glfwSwapBuffers(this->windowManager->getWindow());
        }
    }
}
