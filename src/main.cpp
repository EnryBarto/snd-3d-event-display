#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Constants.hpp"
#include "WindowManager.hpp"
#include "Object.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Projection.hpp"

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
        return -1;
    }
    
    // Debug objects
    snd3D::Object obj(scene);
    std::shared_ptr<snd3D::Shader> flat = std::make_shared<snd3D::Shader>("Flat", "flat.vert", "flat.frag");
    obj.setShader(flat);
    snd3D::Camera camera(glm::vec3(400), glm::vec3(0, 0, 554));
    snd3D::Projection proj(2, 80);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        obj.render(camera.getViewMatrix(), proj.getProjectionMatrix(), camera.getPosition(), false);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(windowMan.getWindow());
    }

    return 0;
}
