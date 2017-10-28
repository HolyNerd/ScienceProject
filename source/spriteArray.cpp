#include <spriteArray.h>

SpriteArray::SpriteArray() {

}
SpriteArray::SpriteArray(int i)
	: _sprites(i)
{

}
SpriteArray::SpriteArray(const SpriteArray&) {

}
SpriteArray::~SpriteArray() {

}

GLfloat SpriteArray::getWidth() {
	GLfloat width = 0;

	for(int i = 0; i < _sprites.size(); i++) { 
		width += _sprites[i].getWidth() * 2;
	}

	return width;
}

void SpriteArray::addSprite(const Sprite& newSprite) {
	_sprites.push_back(newSprite);
}

void SpriteArray::clear() {
	_sprites.clear();
}

void SpriteArray::setPosition(glm::vec2 newPosition) {
	GLfloat offset = 0;

	GLfloat x = newPosition.x;
	GLfloat y = newPosition.y;

	for(int i = 0; i < _sprites.size(); i++) {
		offset += _sprites[i].getWidth();
		_sprites[i].setPosition(glm::vec2(x + offset, y));
		offset += _sprites[i].getWidth();
	}
}

Sprite& SpriteArray::operator[](int index) {
	return _sprites[index]; 
}

void SpriteArray::draw() {
	for(int i = 0; i < _sprites.size(); i++) {
		_sprites[i].update();
		_sprites[i].draw();
	}
}