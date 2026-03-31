#include "Shader.hpp"

#include "Constants.hpp"
#include "ShaderMaker.hpp"

namespace snd3D {

	Shader::Shader(const char* name, const char* vertexShader, const char* fragmentShader) {
		char vS[100], fS[100];
		strcpy_s(vS, constants::paths::SHADER_FOLDER);
		strcat_s(vS, vertexShader);
		strcpy_s(fS, constants::paths::SHADER_FOLDER);
		strcat_s(fS, fragmentShader);

		this->programId = ShaderMaker::createProgram(vS, fS);
		this->name = std::string(name);
	}

	Shader::~Shader() {
		glDeleteProgram(this->getProgramId());
	}

	std::string Shader::getName() {
		return name;
	}

	GLuint Shader::getProgramId() {
		return programId;
	}
}