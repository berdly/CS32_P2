#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
#include <glad/glad.h>
/*
A shader program is a set of rendering instructions used by OpenGL. 
This class handles the dynamic compilation of shaders from text files 
(in this case the vertex and fragment shader) and links them together 
into a usable program. Also provides helper functions for setting 
uniform variables (parameters used for rendering calculations).
This game is simple so we'll share one shader program between all
entities as there's no need for added complexity.
*/
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

	void setMatrix(const std::string&, const float*);
	void setMatrix(unsigned, const float*);

	void setVec(const std::string&, const float*);
	void setVec(unsigned, const float*);
	/*
	template<typename T>
	void setArr(const std::string&, T*);
	template<typename T>
	void setArr(unsigned, T*);
	*/
};
#endif
