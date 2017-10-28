#include <GUI_Text.h>

GUI_Text::GUI_Text() {
	_scale = 1;
}

GUI_Text::~GUI_Text() {

}

GLfloat GUI_Text::getTextWidth() {
	GLfloat width = _sprite_array.getWidth();
	return width;;
}

void GUI_Text::setFont(const char* fontPath) {
	_char.setFont(fontPath);
}

void GUI_Text::setScale(GLfloat scale) {
	_scale = scale;
}

void GUI_Text::setNumber(std::string number) {
	_number = number;
	_feed_array();
}

void GUI_Text::_feed_array() {
	_sprite_array.clear();
	for(int i = 0; i < _number.size(); i++) {
		if(_number[i] == '-') {
			Sprite newChar;
			newChar = _char.getCharacter('-', _scale);
	
			_sprite_array.addSprite(newChar);
			continue;
		}

		int digit = _number[i] - '0';
		
		Sprite newChar;
		newChar = _char.getCharacter(digit, _scale);

		_sprite_array.addSprite(newChar);
	}
}

void GUI_Text::setPosition(glm::vec2 newPosition) {
	_sprite_array.setPosition(newPosition);
}

void GUI_Text::draw() {
	_sprite_array.draw();
}