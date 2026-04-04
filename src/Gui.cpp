#include "App.hpp"

#include "Gui.hpp"
#include "Constants.hpp"

namespace snd3D {

    Gui::Gui(App& app, float fontSize) : app(app) {
        this->fontSize = fontSize;

        // Init ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.FontGlobalScale = this->fontSize;
        io.IniFilename = NULL; // Deactivate ini file
        ImGui::StyleColorsDark(); // Set ImGUI dark theme
        ImGui_ImplGlfw_InitForOpenGL(this->app.windowManager->getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    Gui::~Gui() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Gui::update() {
        // Start ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->drawMenuBar();
    }

    void Gui::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Gui::changeFontSize(float factor) {
        if (this->fontSize * factor < constants::limits::GUI_FONT_SIZE_MIN) return;
        this->fontSize *= factor;
        ImGuiIO& io = ImGui::GetIO();
        io.FontGlobalScale = this->fontSize;
    }

    bool Gui::isPointerOverGui() {
        return ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
    }

    void Gui::drawMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save Image", "Ctrl + S")) {
                    this->app.stateManager.toggleImageExport();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Quit", "Alt + F4")) {
                    this->app.stateManager.close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Font +", "Ctrl + +")) {
                    this->changeFontSize(constants::factors::GUI_FONT_RESIZE);
                }
                if (ImGui::MenuItem("Font -", "Ctrl + -")) {
                    this->changeFontSize(1 / constants::factors::GUI_FONT_RESIZE);
                }
                bool vsyncEnabled = this->app.windowManager->isVsyncActive();
                if (ImGui::MenuItem("V-Sync", "V", vsyncEnabled)) {
                    this->app.windowManager->toggleVsync();
                }
                bool fullScreen = this->app.windowManager->isFullScreen();
                if (ImGui::MenuItem("Full Screen", "F11", fullScreen)) {
                    this->app.windowManager->toggleFullScreen();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Camera")) {
                bool pivot = this->app.settings.isCameraPivotActive();
                if (ImGui::MenuItem("Show Pivot", "P", pivot)) {
                    this->app.settings.toggleCameraPivot();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Zoom In", "Scroll Up")) {
                    this->app.scene->camera->zoom(constants::factors::ZOOM);
                }
                if (ImGui::MenuItem("Zoom Out", "Scoll Down")) {
                    this->app.scene->camera->zoom(-constants::factors::ZOOM);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Move Right", "Right")) {
                    this->app.scene->camera->rotateByAngles(constants::factors::ROTATION_SPEED, 0);
                }
                if (ImGui::MenuItem("Move Left", "Left")) {
                    this->app.scene->camera->rotateByAngles(-constants::factors::ROTATION_SPEED, 0);
                }
                if (ImGui::MenuItem("Move Up", "Up")) {
                    this->app.scene->camera->rotateByAngles(0, constants::factors::ROTATION_SPEED);
                }
                if (ImGui::MenuItem("Move Down", "Down")) {
                    this->app.scene->camera->rotateByAngles(0, -constants::factors::ROTATION_SPEED);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Reset", "R")) {
                    this->app.scene->camera->reset();
                }
                ImGui::EndMenu();
            }

            // Move FPS label at the end of the window
            float fps = ImGui::GetIO().Framerate;
            char fpsLabel[15];
            sprintf(fpsLabel, "%.1f FPS", fps);
            float textWidth = ImGui::CalcTextSize(fpsLabel).x;
            float padding = ImGui::GetStyle().ItemSpacing.x;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - textWidth - padding);
            ImGui::TextDisabled("%s", fpsLabel);

            ImGui::EndMainMenuBar();
        }
    }
}
