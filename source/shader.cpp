

#include <shader.h>
#include <fstream>
#include <iostream>

// Constructors
Shader::Shader() {
	program = 0;
}
Shader::Shader(const std::string shaderName) {
	shaderInfo(shaderName);
	filePath = shaderName;
}
Shader::Shader(const Shader& rhs) {
	filePath = rhs.getFilePath();
	shaderInfo(filePath);
}

Shader& Shader::operator=(const Shader& rhs) {
	filePath = rhs.getFilePath();
	shaderInfo(filePath);

	return *this;
}

Shader::~Shader() {
	glDeleteProgram(program); // if comment - draws only charge, else - draw all, but shity
}

void Shader::shaderInfo(const std::string shaderName) {
	// Creating temp shaders
	filePath = shaderName;

	GLuint vertShader = createShader(GL_VERTEX_SHADER, shaderName + ".vert.glsl");
	GLuint fragShader = createShader(GL_FRAGMENT_SHADER, shaderName + ".frag.glsl");

	// Create Program
	program = glCreateProgram();

	// Attaching and linking
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	#ifdef DEBUG 
		std::cout << "Shader " + shaderName + " compiled succesfully;\n"; 
	#endif

	// Program is linked, so we neednt shaders anymore
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::operator GLuint() {
	return program;
}

std::string Shader::getFilePath() const {
	return filePath;
}

GLuint Shader::createShader(GLenum type, const std::string name) {
	GLuint shader = glCreateShader(type);

	std::string shaderSource = readShader(name);
	
	const char* shaderSrc = shaderSource.c_str();

	glShaderSource(shader, 1, &shaderSrc, NULL);

	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	
	if(isCompiled == GL_FALSE) {
		std::cout << "Shader compilation errror!\n";
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog = new GLchar[maxLength];

		glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

		std::cout << infoLog << "\n";
	}

	return shader;
}
std::string Shader::readShader(const std::string fileName) { 
	std::ifstream file;
	file.open(fileName, std::ifstream::in);

	if(!file.is_open()) {
		std::cerr << "Could not read file" << std::endl;
		return "";
	}

	std::string line = "";
	std::string src;

	while(!file.eof()) {
		std::getline(file, line);
		src.append(line + "\n");
	}
	
	file.close();
	return src;
}
