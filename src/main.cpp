//class to handle dynamic shader loading
#include "shaderprog.h"
//class which represents game objects
#include "entity.h"
//class which handles rendering of entities
#include "renderer.h"
#include "handler.h"
//OpenGL function loading
//window and input handling
#include <GL/glut.h> //i think it goes like this
#include <stdlib.h>
#include <stdio.h>
#include <string>
// Standard Headers
#include <iostream>
#include <vector>
#include <utility>

ShaderProg::ShaderProg(const std::string& vSource, const std::string& fSource) {
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
	catch (std::ifstream::failure) {
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

void ShaderProg::use() const {
	glUseProgram(this->id);
}

unsigned ShaderProg::get_uniform_addr(const std::string& unif) const{
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

void ShaderProg::setMatrix(const std::string& unif, float* data) const{
	glUniformMatrix4fv(this->get_uniform_addr(unif), 1, GL_FALSE, data);
}
void ShaderProg::setMatrix(unsigned addr, float* data) const{
	glUniformMatrix4fv(addr, 1, GL_FALSE, data);
}
int last;
PlayerHandler player;
PlayerBulletHandler bullets;
ShaderProg shaderProg;
bool wasdj[5];

int window2 = 0, window = 0, width = 400, height = 400;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    player.draw();
    bullets.draw();

    glutSwapBuffers(window);
}

void init(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK); // cull back face
    glFrontFace(GL_CW);
    last = glutGet(GLUT_ELAPSED_TIME);
    float dt;
    shaderProg = ShaderProg{ "../shaders/vertex.vert", "../shaders/fragment.frag" };
    shaderProg.use();
    
    player = PlayerHandler{shaderProg};
    bullets = PlayerBulletHandler{shaderProg};
}

void idle(){
    int now = glutGet(GLUT_ELAPSE_TIME);
    float dt = (last - now) / 1000.0f;
    last = now;
    if(player.update(dt, wasdj)){
            bullets.spawn(player.get_coord());
    }
    bullets.update(dt);
    glutPostRedisplay();
}
void reshape (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y) 
{
     switch (key) 
    {    
       case 'w' : wasdj[0] = true;   break;
       case 'a':  wasdj[1] = true;  ;  break;
       case 's' : wasdj[2] = true;  ;  break;
       case 'd' : wasdj[3] = true;  ;  break;
        case 'j' : wasdj[4] = true; ; break;
        default:
            break;
    }
}

void keyboard_up_func(unsigned char key, int x, int y) 
{
     switch (key) 
    {    
       case 'w' : wasdj[0] = false;   break;
       case 'a':  wasdj[1] = false;  ;  break;
       case 's' : wasdj[2] = false;  ;  break;
       case 'd' : wasdj[3] = false;  ;  break;
        case 'j' : wasdj[4] = false; ; break;
        default:
            break;
    }

}

int main(int argc, char **argv)
{
    // Initialization stuff
    glutInit(&argc, argv);
    glutInitContextVersion( 3, 3 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    
    glutInitDisplayMode(GLUT_DOUBLE, GLUT_RGB);
    glutInitWindowSize(width, height);

    // Create  window main
    window = glutCreateWindow("Window 1");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard_func);
    glutReshapeFunc(keyboard_up_func);
    glutInitWindowPosition(100,100);


    // Enter Glut Main Loop and wait for events
    glutMainLoop();
return 0;
}
