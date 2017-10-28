#include <menu.h>
#include <iostream>

Menu::Menu() {
	_text_box.setElementName("textbox1");
	_name_line.setElementImage("Media/GUI/line.png");
}

Menu::~Menu() {

}

bool Menu::isTextBoxAvaliable(std::string tbName, glm::vec2 mousPos) {
	if(_text_box.isVisible() == false) {
		return false;
	}
	if(_text_box.getElementName() == tbName && _text_box.isIn(mousPos))
		return true;
	return false;
}

void Menu::setElementVisible(bool b) {
	_text_box.setElementVisible(b);
	Element::setElementVisible(b);
}

void Menu::setTextBoxText(std::string name, std::string text) {
	_text_box.setText(text);
}

Textbox& Menu::getTextBox() {
	return _text_box;
}

void Menu::draw() {
	if(!_is_visible)
		return;
	Element::draw();

	glm::vec2 tbPosition = _element_position;
	tbPosition.x = tbPosition.x - 0.25;
	tbPosition.y = tbPosition.y + 0.33;
	_text_box.setElementPosition(tbPosition);

	_name_line.setElementSize(_element_width, 0.063);

	glm::vec2 np;
	np.x = _element_position.x;
	np.y = _element_position.y + 0.43;
	_name_line.setElementPosition(np);

	_text_box.draw();
	_name_line.draw();
}