#pragma once

#include <string>
#include <glad/glad.h>

namespace snd3D {
	class Shader {
		public:
			Shader(const char* name, const char* vertexShader, const char* fragmentShader);
			~Shader();
			std::string getName();
			GLuint getProgramId();

		private:
			std::string name;
			GLuint programId;
	};
}