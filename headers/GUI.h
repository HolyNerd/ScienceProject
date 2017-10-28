#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/vec2.hpp>

#include <menu.h>
#include <button.h>
#include <GUI_Cursor.h>

class GUI {
public:
	GUI();
	~GUI();

	const glm::vec2 getMousePosition();

	bool isButtonPressed(std::string buttonName);
	bool isTextBoxAvaliable(std::string textBoxName);
	bool isKeyPressed(int);
	static bool isKeyPressedb;

	void setCursor(GUI_Cursor::cursor_stat);

	void addElement(const Button& newButton);
	void addElement(const Menu& newMenu);

	void setVisibility(const std::string name, bool);

	void setTextBoxText(std::string name, std::string text);

	void display();

	void bindWindow(GLFWwindow*);
	void unbind();

	static bool _mouse_button_pressed;
	static bool _mouse_button_released;
	static bool _mouse_right_button_pressed;
private:
	std::vector<Button> _buttons;
	std::vector<Menu> _menus;
	GUI_Cursor _cursor;
	bool _draw_cursor;

	GLFWwindow* window;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif