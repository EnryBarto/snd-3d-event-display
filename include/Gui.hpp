#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

            void drawMenuBar();
    };
}