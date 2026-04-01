#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/fwd.hpp>

#include "Material.hpp"

namespace snd3D {
    class Shader {
        public:
            Shader(std::string name, std::string vertexShader, std::string fragmentShader);
            ~Shader();
            std::string getName();
            GLuint getProgramId();
            void use();
            void bindUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& camPos, Material* material);

        private:
            std::string name;
            GLuint programId;

            // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
            GLint uniform_Projection = -1;
            GLint uniform_Model = -1;
            GLint uniform_View = -1;
            GLint uniform_ViewPos = -1;
            GLint uniform_MaterialAmbient = -1;
            GLint uniform_MaterialDiffuse = -1;
            GLint uniform_MaterialSpecular = -1;
            GLint uniform_MaterialShininess = -1;
    };
}
