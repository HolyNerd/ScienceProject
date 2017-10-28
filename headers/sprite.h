
#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/mat2x2.hpp>
#include <shader.h>

class Sprite {
public:
	Sprite();
	Sprite(const Sprite& rhs);
	~Sprite();

	void init();
	
	const GLfloat getWidth();

	void setRect(glm::vec2 centerPosition, GLfloat width, GLfloat height);
	void setShader(const char*);
	void setTexture(const char* fileName);
	
	void setTextureCoord(glm::vec2 coords[4]);
	void setPosition(glm::vec2 newPosition);
	void rotate(GLfloat angle);

	void update();
	void draw();

	Sprite& operator=(const Sprite& rhs);

private:
	GLuint* buffers;
	GLuint vao;
	GLuint texture;
	Shader shader;

	enum bufferIDs { vertexBuffer, texCords, numBuffers };

	glm::vec2 texCoords[4];
	glm::vec2 coords[4];
	glm::vec2 center_coordVectors[4];
	glm::vec2 center;

	const char* texturePath;
};

#endif