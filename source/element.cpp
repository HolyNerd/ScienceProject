#include <iostream>
#include <element.h>

Element::Element() {
	_element_width = 0.05;
	_element_height = 0.05;
	_element_position = glm::vec2(0.0f, 0.0f);
	_element_image.init();
	_element_image.setShader("Shaders/button");
	_is_visible = true;
}

Element::Element(const Element& rhs){
	_element_image.init();
	_element_image.setShader("Shaders/button");

	_element_width = rhs._element_width;
	_element_height = rhs._element_height;
	_element_position = rhs._element_position;
	_element_name = rhs._element_name;
	_element_texture_path = rhs._element_texture_path;
	_is_visible = rhs._is_visible;

	_element_image.setPosition(_element_position);
	_element_image.setRect(_element_position, _element_width, _element_height);
	_element_image.setTexture(_element_texture_path);
}

Element::~Element() {

}

GLfloat Element::getElementWidth() const {
	return _element_width;
}

bool Element::isVisible() const {
	return _is_visible;
}

bool Element::isIn(glm::vec2 point) {
	if(!_is_visible)
		return false;
		
	glm::vec2 top_left;
	glm::vec2 down_right;

	top_left.x = _element_position.x - _element_width/2;
	down_right.x = _element_position.x + _element_width/2;
	top_left.y = _element_position.y + _element_height/2;
	down_right.y = _element_position.y - _element_height/2;

	Area area { top_left, down_right };

	if(area.isInArea(point)) 
		return true;
	return false;
}

void Element::setElementImage(const char* path) {
	_element_texture_path = path;
	_element_image.setTexture(_element_texture_path);
}
void Element::setElementName(const std::string& name) {
	_element_name = name;
}
void Element::setElementSize(GLfloat width, GLfloat height) {
	_element_image.setRect(_element_position, width, height);
	_element_width = width;
	_element_height = height;
}
void Element::setElementPosition(glm::vec2 newPosition) {
	_element_image.setPosition(newPosition);
	_element_position = newPosition;
}
void Element::setElementVisible(bool visibility) {
	_is_visible = visibility;
}

const std::string& Element::getElementName() const {
	return _element_name;
}

void Element::draw() {
	if(!_is_visible)
		return;

	_element_image.update();
	_element_image.draw();
}