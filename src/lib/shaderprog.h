#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

typedef std::filesystem::path Path;

#include <glad/glad.h>
class ShaderProg {
	unsigned id;
public:
	ShaderProg(const Path& vSource, const Path& fSource);
	void use();
	unsigned get_uniform_addr(const std::string&);

	void setBool(const std::string&, bool);
	void setBool(unsigned, bool);

	void setInt(const std::string&, int);
	void setInt(unsigned, int);

	void setFloat(const std::string&, float);
	void setFloat(unsigned, float);
};
#endif
