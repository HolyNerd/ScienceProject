#ifndef MENU_H
#define MENU_H

#include <string>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <range.h>
#include <sprite.h>

#include <GL/glfw3.h>
#include <element.h>
#include <textbox.h>

class Menu : public Element {
public:
	Menu();
	~Menu();

	void setTextBoxText(std::string name, std::string text);

	void setElementVisible(bool);
	bool isTextBoxAvaliable(std::string textBoxName, glm::vec2 mousPos);

	Textbox& getTextBox();

	void draw();
private:
	Textbox _text_box;
	Element _name_line;
};

#endif