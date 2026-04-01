#include "GpuMesh.hpp"

#include <iostream>

#include "Constants.hpp"

using namespace std;

namespace snd3D {

    GpuMesh::~GpuMesh() {
        // Free GPU resources when the mesh is destroyed
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vboVertices);
        glDeleteBuffers(1, &this->vboColors);
        glDeleteBuffers(1, &this->vboNormals);
        glDeleteBuffers(1, &this->eboIndices);
    }

    void GpuMesh::initBuffers(vector<glm::vec3>& vertices, vector<glm::vec4>& colors, vector<glm::vec3>& normals, vector<GLuint>& indices, glm::vec3 anchorPosition) {

        if (this->vao != 0) {
            cerr << "VAO already initialized" << endl;
            return;
        }

        if (vertices.size() == 0) {
            cerr << "Can't create VAO without vertices" << endl;
            return;
        }

        if (colors.size() != vertices.size()) {
            cerr << "The size of colors must match the size of vertices" << endl;
            return;
        }

        if (normals.size() != vertices.size()) {
            cerr << "The size of normals must match the size of vertices" << endl;
            return;
        }

        this->numIndices = indices.size();
        this->numVertices = vertices.size();

        // Add the anchor to the vectors so it's copied into the VBOs
        vertices.push_back(anchorPosition);
        colors.push_back(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));
        normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f)); // Dummy normal
        indices.push_back(this->numVertices);

        // Generate the VAO and store the location
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        // Generates, activates and fills the vertices VBO
        glGenBuffers(1, &this->vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        // Loading the vertices VBO into layer 0
        glVertexAttribPointer(VERTICES_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(VERTICES_LAYER);

        // Generates, activates and fills the colors VBO
        glGenBuffers(1, &this->vboColors);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), colors.data(), GL_STATIC_DRAW);

        // Loading the colors VBO into layer 1
        glVertexAttribPointer(COLORS_LAYER, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(COLORS_LAYER);

        // Generates, activates and fills the normals VBO
        glGenBuffers(1, &this->vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboNormals);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

        // Loading the normals VBO into layer 2
        glVertexAttribPointer(NORMALS_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(NORMALS_LAYER);

        // Generates, activates and fills the EBO
        glGenBuffers(1, &this->eboIndices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboIndices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        // VAO, VBO and EBO unbind
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Restore the geometry after the anchor is copied
        vertices.pop_back();
        colors.pop_back();
        normals.pop_back();
        indices.pop_back();
    }

    void GpuMesh::setModes(GLenum renderMode) {
        this->drawMode = renderMode;
    }

    void GpuMesh::setShader(std::shared_ptr<Shader> shader) {
        this->shader = shader;
    }

    void GpuMesh::render(const glm::mat4& modelMatrix, bool showAnchor, Material* material) {

        if (this->vao == 0) {
            cerr << "ATTENTION!!! VAO not initialized" << endl;
            return;
        }

        if (!this->shader) {
            cerr << "ATTENTION!!! Shader not set" << endl;
            return;
        }

        this->shader->bindLocalUniforms(modelMatrix, material);

        // RENDER!
        glBindVertexArray(this->vao);
        glDrawElements(this->drawMode, this->numIndices, GL_UNSIGNED_INT, 0);

        if (showAnchor) {
            glPointSize(constants::ANCHOR_SIZE);
            glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(this->numIndices * sizeof(GLuint)));
        }
    }
}
