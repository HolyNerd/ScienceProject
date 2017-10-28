
#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include <GL/glew.h>

#include <glm/vec2.hpp>

#include <range.h>
#include <sprite.h>

#include <GL/glfw3.h>

class Element {
public:

	Element();
	Element(const Element&);
	~Element();

	bool isIn(glm::vec2 point);
	bool isVisible() const;

	void setElementName(const std::string& newName);
	void setElementSize(GLfloat newWidth, GLfloat newHeight);
	void setElementPosition(glm::vec2 newPosition);
	void setElementImage(const char* path);
	void setElementVisible(bool visibility);

	const std::string& getElementName() const;

	GLfloat getElementWidth() const;

	void draw();

protected:

	Sprite _element_image;

	GLfloat _element_width;
	GLfloat _element_height;

	glm::vec2 _element_position;

	const char* _element_texture_path;

	std::string _element_name;

	bool _is_visible;
	
};

#endif