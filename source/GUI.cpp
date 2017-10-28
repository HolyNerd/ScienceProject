
#include <GUI.h>
#include <iostream>

GUI::GUI() {
	_cursor.setCursorSprite(GUI_Cursor::ARROW, 
	"Media/GUI/cursor_arrow.png");
	_cursor.setCursorSprite(GUI_Cursor::HAND, 
		"Media/GUI/cursor_hand.png");
	_cursor.setCursorSprite(GUI_Cursor::TEXT, 
		"Media/GUI/cursor_text.png");
}

GUI::~GUI() {

}

bool GUI::_mouse_button_pressed = false;
bool GUI::_mouse_button_released = false;
bool GUI::_mouse_right_button_pressed = false;
bool GUI::isKeyPressedb = false;

void GUI::unbind() {
	window = nullptr;
}

void GUI::setTextBoxText(std::string s, std::string text) {
	_menus[0].setTextBoxText("df", text);
}

void GUI::setCursor(GUI_Cursor::cursor_stat cs) {
	_cursor.setCursor(cs);
}

bool GUI::isButtonPressed(std::string buttonName) {
	if(glfwGetTime() < 0.3f)
		return false;

	glm::vec2 mousePosition = getMousePosition();

	for(Button& button : _buttons) {
		if(button.getElementName() == buttonName && button.isIn(mousePosition)) {
			if(_mouse_button_pressed == true) {
				glfwSetTime(0.0f);
				button.setPress(true);
				return true;
			}
			else if (_mouse_button_released == true)  {
				button.setPress(false);
				return false;
			}
		}
	}	

	return false;
}
bool GUI::isTextBoxAvaliable(std::string textBoxName) {
	if(glfwGetTime() < 0.3)
		return false;

	static bool edit_mode = false;

	glm::vec2 mousePosition = getMousePosition();

	for(Menu& m : _menus) {
		if(m.isTextBoxAvaliable(textBoxName, mousePosition)) {
			if(_mouse_button_pressed == true) {
				glfwSetTime(0.0f);
				edit_mode = !edit_mode;
				m.getTextBox().editMode(edit_mode);
			//	return true;
			}
			else if (_mouse_button_released == true)  {
			//	return false;
			}
		}
		if(!m.isTextBoxAvaliable(textBoxName, mousePosition)) {
			if(_mouse_button_pressed == true) {
				edit_mode = false;
				m.getTextBox().editMode(false);
			}
		}
	}
//	return false;

	return edit_mode;
}

const glm::vec2 GUI::getMousePosition() {
	int winWidth, winHeight;
	double cursorxPos, cursoryPos;
	
	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwGetCursorPos(window, &cursorxPos, &cursoryPos);

	cursorxPos = (2.0f * cursorxPos) / winWidth - 1;
	cursoryPos = 1.0f - (2.0f * cursoryPos) / winHeight;

	glm::vec2 cursorCoord(cursorxPos, cursoryPos);
	return cursorCoord;
}

void GUI::addElement(const Button& newButton) {
	_buttons.push_back(newButton);
}
void GUI::addElement(const Menu& newMenu) {
	_menus.push_back(newMenu);
}

void GUI::setVisibility(const std::string name, bool visibility) {
	for(Menu& m : _menus) 
		if(m.getElementName() == name) {
			m.setElementVisible(visibility);
			return;
		}
	for(Button& b : _buttons) 
		if(b.getElementName() == name) {
			b.setElementVisible(visibility);
			return;
		}
}

bool GUI::isKeyPressed(int key) {
	//if(glfwGetTime() < 0.3f && key != GLFW_KEY_BACKSPACE)
	//	return false;
	if(glfwGetTime() < 0.15f)
		return false;
	

	int state = glfwGetKey(window, key);

	if(state == GLFW_PRESS) {
		glfwSetTime(0.0f);
		return true;
	}
	return false;
}

void GUI::display() {
	for(Button& b : _buttons)
		b.draw();
	for(Menu& m: _menus)
		m.draw();
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if(_menus[0].getTextBox().isIn(getMousePosition())) {
		setCursor(GUI_Cursor::TEXT);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		_cursor.draw(getMousePosition());
	}
}

void GUI::bindWindow(GLFWwindow* win) {
	window = win;

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, 0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
		GUI::isKeyPressedb = true;
	else
		GUI::isKeyPressedb = false;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		GUI::_mouse_button_pressed = true;
		GUI::_mouse_button_released = false;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		GUI::_mouse_button_pressed = false;
		GUI::_mouse_button_released = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		GUI::_mouse_right_button_pressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		GUI::_mouse_right_button_pressed = false;
	}
}

