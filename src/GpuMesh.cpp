#include "GpuMesh.hpp"

#include <iostream>

using namespace glm;
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

    void GpuMesh::initBuffers(vector<vec3>& vertices, vector<vec4>& colors, vector<vec3>& normals, vector<GLuint>& indices, vec3 anchorPosition) {

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
        colors.push_back(vec4(0.6f, 0.6f, 0.6f, 1.0f));
        normals.push_back(vec3(0.0f, 1.0f, 0.0f)); // Dummy normal
        indices.push_back(this->numVertices);

        // Generate the VAO and store the location
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        // Generates, activates and fills the vertices VBO
        glGenBuffers(1, &this->vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

        // Loading the vertices VBO into layer 0
        glVertexAttribPointer(VERTICES_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(VERTICES_LAYER);

        // Generates, activates and fills the colors VBO
        glGenBuffers(1, &this->vboColors);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_STATIC_DRAW);

        // Loading the colors VBO into layer 1
        glVertexAttribPointer(COLORS_LAYER, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(COLORS_LAYER);

        // Generates, activates and fills the normals VBO
        glGenBuffers(1, &this->vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, this->vboNormals);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);

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
}
