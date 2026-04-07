#pragma once

#include <string>

#include <glad/glad.h>

namespace snd3D {
    class ShaderMaker {
        public:
            static GLuint createProgram(std::string vertexfilename, std::string fragmentfilename);
            static char* readShaderSource(std::string shaderFile);

        private:
            ShaderMaker() {}
    };
}
