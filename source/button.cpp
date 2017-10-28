
#include <iostream>

#include <button.h>

Button::Button() { }

Button::Button(const Button& rhs) : Element(rhs) {
	_pressed_button_image_path = rhs._pressed_button_image_path;
}
Button::~Button() {

}


void Button::setPress(bool isPressed) {
	if(isPressed) 
		_element_image.setTexture(_pressed_button_image_path);
	else 
		_element_image.setTexture(_element_texture_path);
}

void Button::setPressedButtonImage(const char* filePath) {
	_pressed_button_image_path = filePath;
}

void Button::draw() {
	if(glfwGetTime() > 0.3) 
		_element_image.setTexture(_element_texture_path);
	Element::draw();
}