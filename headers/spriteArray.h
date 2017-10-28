
#ifndef SPRITE_ARRAY
#define SPRITE_ARRAY

#include <glm/vec2.hpp>

#include <vector>
#include <sprite.h>

class SpriteArray {
public:
	SpriteArray();
	SpriteArray(int);
	SpriteArray(const SpriteArray&);
	~SpriteArray();

	void addSprite(const Sprite& newSprite);

	void setPosition(glm::vec2 newPosition);

	void clear();

	void draw();

	Sprite& operator[](int index);

	GLfloat getWidth();

private:
	std::vector<Sprite> _sprites;
};

#endif