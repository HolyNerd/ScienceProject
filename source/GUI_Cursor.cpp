#include <GUI_Cursor.h>

GUI_Cursor::GUI_Cursor()
	: _cursor_sprites(3) 
{
	_cs = ARROW;
}

GUI_Cursor::~GUI_Cursor() {

}

void GUI_Cursor::setCursorSprite(cursor_stat cs,
	const char* im_path)
{
	Sprite& cSprite = _cursor_sprites[cs];

	cSprite.init();
	cSprite.setShader("Shaders/button");
	cSprite.setRect(glm::vec2(0,0), 0.05, 0.05);
	cSprite.setTexture(im_path);
}

void GUI_Cursor::setCursor(cursor_stat cs) {
	_cs = cs;
}
void GUI_Cursor::draw(glm::vec2 position) {
	_cursor_sprites[_cs].setPosition(position);
	_cursor_sprites[_cs].update();
	_cursor_sprites[_cs].draw();
}