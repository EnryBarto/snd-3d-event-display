#include "ui/Gui.hpp"

#include "core/App.hpp"
#include "core/Constants.hpp"
#include "scene/Node.hpp"

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
        this->drawInspector();
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
            this->menuBarHeight = ImGui::GetWindowSize().y;
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
            char label[50];
            sprintf(label, "%s - %.1f FPS", appStateToString(this->app.stateManager.getCurrentState()), fps);
            float textWidth = ImGui::CalcTextSize(label).x;
            float padding = ImGui::GetStyle().ItemSpacing.x;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - textWidth - padding);
            ImGui::TextDisabled("%s", label);

            ImGui::EndMainMenuBar();
        }
    }

    void Gui::drawInspector() {

        ImGui::SetNextWindowSizeConstraints(
            ImVec2(0.0f, 0.0f), // No min size
            ImVec2(
                this->app.windowManager->getCurrentResolution().x - constants::sizes::PADDING * 2,
                this->app.windowManager->getCurrentResolution().y - this->menuBarHeight - constants::sizes::PADDING * 2
            )
        );

        ImGui::SetNextWindowPos(ImVec2(constants::sizes::PADDING, this->menuBarHeight + constants::sizes::PADDING), ImGuiCond_Always);

        ImGui::SetNextWindowSize(ImVec2(400, this->app.windowManager->getCurrentResolution().y - this->menuBarHeight - constants::sizes::PADDING * 2), ImGuiCond_Once);

        ImGui::Begin("SCENE", NULL, ImGuiWindowFlags_NoMove);

        this->drawObjectTree("SND", this->app.scene->detector.get());

        ImGui::End();
    }

    void Gui::drawObjectTree(const std::string& label, Object* obj) {
        if (!obj || !obj->rootNode) return;

        ImGui::PushID(obj); // Create unique ID to identify the object into the gui

        ImGui::Checkbox("##objActive", &obj->active);
        ImGui::SameLine();

        if (ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::BeginChild((label + "Tree").c_str(), ImVec2(0, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY, ImGuiWindowFlags_HorizontalScrollbar);

            if (ImGui::Button("Show All")) {
                obj->setGlobalActive(true);
            }
            ImGui::SameLine();
            if (ImGui::Button("Hide All")) {
                obj->setGlobalActive(false);
            }

            this->drawNodeTree(obj->rootNode.get()); // Start showing children recursively

            ImGui::EndChild();
        }

        ImGui::PopID(); // End using this object ID
    }

    void Gui::drawNodeTree(Node* node) {
        if (!node) return;

        ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

        if (node->childrenNode.empty() && node->meshes.empty()) {
            nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        ImGui::PushID(node); // Create unique ID to identify the node into the gui

        ImGui::Checkbox("##nodeActive", &node->active);
        ImGui::SameLine();

        bool isOpened = ImGui::TreeNodeEx((void*)node, nodeFlags, "[Node] - %s", node->name.c_str()); // Create the tree for this node

        if (isOpened) {
            for (auto& mesh : node->meshes) {
                ImGui::PushID(mesh.get()); // Create unique ID to identify the mesh into the gui

                ImGuiTreeNodeFlags meshFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;

                ImGui::Checkbox("##meshActive", &mesh->active);
                ImGui::SameLine();

                ImGui::TreeNodeEx((void*)mesh.get(), meshFlags, "[Mesh] - %s", mesh->name.c_str());

                ImGui::PopID();
            }

            for (auto& child : node->childrenNode) {
                drawNodeTree(child.get());
            }

            // If the node isn't a leaf, close the TreeNodeEx
            if (!(nodeFlags & ImGuiTreeNodeFlags_Leaf)) {
                ImGui::TreePop();
            }
        }

        ImGui::PopID();
    }
}
