#ifndef BUTTON_H
#define BUTTON_H

#include <element.h>

class Button : public Element {
public:
	Button();
	Button(const Button&);
	~Button();

	void setPressedButtonImage(const char* filePath);
	void setPress(bool isPressed);

	void draw();
private:
	const char* _pressed_button_image_path;
};

#endif