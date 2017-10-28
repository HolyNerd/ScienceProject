#ifndef GUI_CURSOR_H
#define GUI_CURSOR_H

#include <spriteArray.h>
#include <glm/vec2.hpp>

class GUI_Cursor {
public:
	
	enum cursor_stat{ ARROW, HAND, TEXT, NONE };

	GUI_Cursor();
	~GUI_Cursor();

	void setCursor(cursor_stat);
	void draw(glm::vec2 position);
	void setCursorSprite(cursor_stat, const char* im_path);

private:
	SpriteArray _cursor_sprites;
	cursor_stat _cs;
};

#endif