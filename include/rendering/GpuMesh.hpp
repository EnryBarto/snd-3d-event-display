#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "rendering/Shader.hpp"
#include "rendering/Material.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace snd3D {
    class GpuMesh {
        public:
            ~GpuMesh();
            void initBuffers(
                std::vector<glm::vec3>& vertices,
                std::vector<glm::vec4>& colors,
                std::vector<glm::vec3>& normals,
                std::vector<GLuint>& indices,
                glm::vec3 anchorPosition
            );
            void setModes(GLenum renderMode);
            void setShader(std::shared_ptr<Shader> shader);
            void render(const glm::mat4& modelMatrix, bool showAnchor, Material* material);

        private:
            unsigned int numIndices, numVertices; // The number of vertices and indices without considering the anchor

            // GPU buffers location
            GLuint vao = 0;     // Vertex Array Object (VAO) identifier
            GLuint vboVertices = 0; // Vertex Buffer Object (VBO) identifier containing the object's vertex coordinates
            GLuint vboColors = 0;   // VBO identifier containing the object's vertex colors
            GLuint vboNormals = 0;  // VBO identifier containing the vertex normals
            GLuint eboIndices = 0;  // Element Buffer Object (EBO) identifier

            GLenum drawMode = GL_TRIANGLES; // Vertex interpretation mode for the rendering stage (ex. GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_LINES, GL_POINTS)
            std::shared_ptr<Shader> shader;

            //bool usingBlinnPhong = true; // Enable default blinn phong if supported
    };
}
