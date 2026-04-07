#pragma once

#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "scene/Object.hpp"
#include "scene/Node.hpp"

namespace snd3D {
    class App;

    class Gui {
        public:
            Gui(App& app, float fontSize);
            ~Gui();
            void update();
            void render();
            void changeFontSize(float factor);
            bool isPointerOverGui();

        private:
            App& app; // Keep reference to App object
            float fontSize;
            float menuBarHeight;

            void drawMenuBar();
            void drawInspector();
            void drawObjectTree(const std::string& label, Object* obj);
            void drawNodeTree(Node* node);
    };
}
