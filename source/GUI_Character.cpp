#include <GUI_Character.h>

GUI_Char::GUI_Char() {
	_width[0] = 125;
	_width[1] = 190;
	_width[2] = 190;
	_width[3] = 205;
	_width[4] = 195;
	_width[5] = 200;
	_width[6] = 175;
	_width[7] = 205;
	_width[8] = 215;
	_width[9] = 230;
	_width[10] = 175;
}
GUI_Char::~GUI_Char() {

}

void GUI_Char::setFont(const char* fontPath) {
	_font_path = fontPath;
}

const Sprite GUI_Char::getCharacter(int digit, GLfloat scale) {
	Sprite character;
	character.init();

	GLfloat charWidth;
	if(digit == 0)
		charWidth = _width[9] / 900.0;
	else
		charWidth = _width[digit-1] / 900.0;
	GLfloat charHeight = 0.3;

	charWidth *= scale;
	charHeight *= scale;

	character.setRect (
		glm::vec2(0.0, 0.0), 
		charWidth, charHeight
	);

	character.setShader("Shaders/charge");
	character.setTexture(_font_path);

	GLfloat offset = _get_offset(digit);
	GLfloat start = _get_start(digit);

	glm::vec2 texCoord[4];
	
	texCoord[0] = glm::vec2(start, 1.0);
	texCoord[1] = glm::vec2(offset, 1.0);
	texCoord[2] = glm::vec2(offset, 0.0);
	texCoord[3] = glm::vec2(start, 0.0);

	character.setTextureCoord(texCoord);

	return character;
}

const Sprite GUI_Char::getCharacter(char digit, GLfloat scale) {
	Sprite character;
	character.init();

	GLfloat charWidth;
	charWidth = 175 / 900.0;
	GLfloat charHeight = 0.3;

	charWidth *= scale;
	charHeight *= scale;

	character.setRect (
		glm::vec2(0.0, 0.0), 
		charWidth, charHeight
	);

	character.setShader("Shaders/charge");
	character.setTexture(_font_path);

	GLfloat offset = 1;
	GLfloat start = 1920.0 / 2094;

	glm::vec2 texCoord[4];
	
	texCoord[0] = glm::vec2(start, 1.0);
	texCoord[1] = glm::vec2(offset, 1.0);
	texCoord[2] = glm::vec2(offset, 0.0);
	texCoord[3] = glm::vec2(start, 0.0);

	character.setTextureCoord(texCoord);

	return character;
}

GLfloat GUI_Char::_get_offset(int digit) {
	GLfloat w = 2094.0;
	GLfloat offset = 0;

	if(digit == 0)
		digit = 10;
	
	for(int i = 0; i < digit; i++) {
		offset += _width[i];
	}

	return offset / w;
}
GLfloat GUI_Char::_get_start(int digit) {
	GLfloat w = 2094;
	GLfloat start = 0;

	if(digit == 0)
		digit = 10;

	for(int i = 1; i < digit; i++) {
		start += _width[i-1];
	}

	return start / w;
}