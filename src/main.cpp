#include <iostream>

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Constants.hpp"
#include "WindowManager.hpp"

#include "Object.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

int main() {

    snd3D::WindowManager windowMan(
            snd3D::constants::window::DEFAULT_WIDTH,
            snd3D::constants::window::DEFAULT_HEIGHT,
            snd3D::constants::window::NAME,
            snd3D::constants::window::DEFAULT_VSYNC
    );

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("assets/geometries/SND.gltf",
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices |
        aiProcess_ImproveCacheLocality
    );

    if (!scene) {
        std::cerr << "Error loading file: " << importer.GetErrorString() << std::endl;
    } else {
        snd3D::Object obj(scene);
    }

    // Game Loop
    while (!glfwWindowShouldClose(windowMan.getWindow())) {
        glfwPollEvents();

        if (glfwGetKey(windowMan.getWindow(), GLFW_KEY_F11)) windowMan.toggleFullScreen();
        
        // Start ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Info");
        ImGui::Text("Hello from ImGui!");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

        // Rendering
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(windowMan.getWindow());
    }

    return 0;
}
