#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
#include <glad/glad.h>

class ShaderProg {
	unsigned id;
public:
	ShaderProg(const fs::path& vSource, const fs::path& fSource);
	void use();
	unsigned get_uniform_addr(const std::string&);

	void setBool(const std::string&, bool);
	void setBool(unsigned, bool);

	void setInt(const std::string&, int);
	void setInt(unsigned, int);

	void setFloat(const std::string&, float);
	void setFloat(unsigned, float);

	void setMatrix(const std::string&, float*);
	void setMatrix(unsigned, float*);
};
#endif
