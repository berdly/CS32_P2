#include "shaderprog.h"
ShaderProg::ShaderProg(const fs::path& vSource, const fs::path& fSource) {
	std::string vStr, fStr;
	std::ifstream vFile, fFile;
	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vFile.open(vSource);
		fFile.open(fSource);
		std::stringstream vBuf, fBuf;
		vBuf << vFile.rdbuf();
		fBuf << fFile.rdbuf();
		vStr = vBuf.str();
		fStr = fBuf.str();
	}
	catch (const std::ifstream::failure&) {
		std::cout << "ShaderProg file read error!\n";
	}
	const char* vCode{ vStr.c_str() };
	const char* fCode{ fStr.c_str() };

	unsigned vAddr{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vAddr, 1, &vCode, nullptr);
	glCompileShader(vAddr);
	int success;
	glGetShaderiv(vAddr, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vAddr, 512, NULL, infoLog);
		std::cout << "Error: Vertex ShaderProg Compilation Failed:(\n" << infoLog << '\n';
	}

	unsigned fAddr{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fAddr, 1, &fCode, nullptr);
	glCompileShader(fAddr);
	glGetShaderiv(fAddr, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fAddr, 512, NULL, infoLog);
		std::cout << "Error: Vertex ShaderProg Compilation Failed:(\n" << infoLog << '\n';
	}

	unsigned shaderProgram{ glCreateProgram() };
	glAttachShader(shaderProgram, vAddr);
	glAttachShader(shaderProgram, fAddr);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error: Vertex ShaderProg Compilation Failed:(\n" << infoLog << '\n';
	}

	this->id = shaderProgram;
	glDeleteShader(vAddr);
	glDeleteShader(fAddr);
}

void ShaderProg::use() {
	glUseProgram(this->id);
}

unsigned ShaderProg::get_uniform_addr(const std::string& unif) {
	return glGetUniformLocation(this->id, unif.c_str());
}
void ShaderProg::setBool(const std::string& unif, bool data) {
	glUniform1i(this->get_uniform_addr(unif), static_cast<int>(data));
}
void ShaderProg::setBool(unsigned addr, bool data) {
	glUniform1i(addr, static_cast<int>(data));
}

void ShaderProg::setInt(const std::string& unif, int data) {
	glUniform1i(this->get_uniform_addr(unif), data);
}
void ShaderProg::setInt(unsigned addr, int data) {
	glUniform1i(addr, data);
}

void ShaderProg::setFloat(const std::string& unif, float data) {
	glUniform1f(this->get_uniform_addr(unif), data);
}
void ShaderProg::setFloat(unsigned addr, float data) {
	glUniform1f(addr, data);
}

void ShaderProg::setMatrix(const std::string& unif, const float* data) {
	glUniformMatrix4fv(this->get_uniform_addr(unif), 1, GL_FALSE, data);
}
void ShaderProg::setMatrix(unsigned addr, const float* data) {
	glUniformMatrix4fv(addr, 1, GL_FALSE, data);
}

void ShaderProg::setVec(const std::string& unif, const float* data) {
	glUniform3fv(this->get_uniform_addr(unif), 1, data);
}
void ShaderProg::setVec(unsigned addr, const float* data) {
	glUniform3fv(addr, 1, data);
}
