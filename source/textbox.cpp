#include <textbox.h>
#include <iostream>
#include <GUI.h>

Textbox::Textbox() {
	_edit_mode = false;
	_carriage.init();	
	_number = "";
	setElementImage("Media/GUI/textbox.png");
	setElementSize(0.21 * 2, 0.05 * 2);

	_text.setFont("Media/GUI/font.png");
	_text.setPosition(_element_position);
}
Textbox::Textbox(const Textbox& rhs) : Element(rhs) {
	_number = rhs._number;
	_text = rhs._text;
}
Textbox::~Textbox() {

}

bool Textbox::editMode() {
	return _edit_mode;
}
bool Textbox::editMode(bool editModeOn) {
	_edit_mode = editModeOn;
	return _edit_mode;
}

void Textbox::setText(std::string text) {
	_number = text;
	_text.setScale(0.2);
	_text.setNumber(text);

	GLfloat offset = 0.01;

	glm::vec2 textBoxPosition;
	textBoxPosition.y = _element_position.y;
	textBoxPosition.x = _element_position.x - getElementWidth()/2 + offset;

	_text.setPosition(textBoxPosition);
}

void Textbox::draw() {
	Element::draw();

	if(_number != "")
		_text.draw();

	if(_edit_mode) {

		glm::vec2 carriagePosition;
		carriagePosition.y = _element_position.y;
		carriagePosition.x = _element_position.x - getElementWidth()/2 + 0.02 + _text.getTextWidth();

		_carriage.init();		
		_carriage.setRect(carriagePosition, 0.01, 0.07);
		_carriage.setShader("Shaders/carriage");
		_carriage.update();	
		
		_carriage.draw();
	}	
}