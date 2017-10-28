#ifndef GUI_CHAR_H
#define GUI_CHAR_H

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <string>

#include <sprite.h>
#include <shader.h>

class GUI_Char{
public:

	GUI_Char();
	~GUI_Char();

	void setFont(const char* fontPath);

	const Sprite getCharacter(int digit, GLfloat scale);
	const Sprite getCharacter(char digit, GLfloat scale);

private:
	const char* _font_path;
	GLfloat _width[10];

	GLfloat _get_offset(int digit);
	GLfloat _get_start(int digit);
};

#endif