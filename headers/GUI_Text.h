#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include <string>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <GUI_Character.h>
#include <sprite.h>
#include <spriteArray.h>

class GUI_Text {
public:
	GUI_Text();
	~GUI_Text();

	void setFont(const char* fontPath);

	void setNumber(std::string number);
	void setPosition(glm::vec2 newPosition);
	void setScale(GLfloat scale);

	GLfloat getTextWidth();

	void draw();

private:
	GUI_Char _char;

	std::string _number;

	SpriteArray _sprite_array;

	void _feed_array();

	GLfloat _scale;
};

#endif