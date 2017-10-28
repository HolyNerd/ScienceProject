
#include <application.h>

#include <chrono>
#include <sstream>
#include <string>
#include <iostream>

#include <line.h>
#include <button.h>
#include <functions.h>

#define HIGH_QUALITY

Application::Application(GLFWwindow* win)
	: window(win)
{
	
	std::cout << "App creating\n";

	std::cout << "window created\n";

	chargeValue = 1;

	mode = DISPLAY;

	isUpdated = false;

#ifdef HIGH_QUALITY

	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_BLEND, GL_NICEST);

#endif

	std::cout << "background creating\n";

	background.init();
	background.setRect(glm::vec2(0.0, 0.0), 2.0f, 2.0f);
	background.setTexture("Media/background_8.png");
	background.setShader("Shaders/background");
	background.update();
}

Application::~Application() {
}


void Application::init() {

	std::cout << "init()\n";

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	GLfloat buttonWidth = 0.22;
	GLfloat buttonHeight = 0.074;


	GLfloat posx = -0.86;
	GLfloat posy = 0.95;
	GLfloat scrnOffsety = 0.074;

	std::cout << "button1\n";

	Button button;
	button.setElementPosition(glm::vec2(posx, posy));
	button.setElementSize(buttonWidth, buttonHeight);
	button.setElementImage("Media/GUI/button2_add.png");
	button.setPressedButtonImage("Media/GUI/button2_add_2.png");
	button.setElementName("Button1");
	gui.addElement(button);

	std::cout << "button2\n";

	button.setElementPosition(glm::vec2(posx, posy - scrnOffsety));
	button.setElementImage("Media/GUI/button2_move.png");
	button.setPressedButtonImage("Media/GUI/pressed_button2_move.png");
	button.setElementName("Button2");
	gui.addElement(button);

	std::cout << "button3\n";

	button.setElementPosition(glm::vec2(posx, posy - scrnOffsety*2));
	button.setElementImage("Media/GUI/button2_delete.png");
	button.setPressedButtonImage("Media/GUI/pressed_button2_delete.png");
	button.setElementName("Button3");
	gui.addElement(button);

	button.setElementPosition(glm::vec2(posx, posy - scrnOffsety*3));
	button.setElementImage("Media/GUI/button2_settings.png");
	button.setPressedButtonImage("Media/GUI/button2_settings2.png");
	button.setElementName("Button4");
	gui.addElement(button);

	std::cout << "menu creating\n";

	Menu menu;
	menu.setElementPosition(glm::vec2(-0.5, -0.5));
	menu.setElementSize(1.0, 1.0);
	menu.setElementImage("Media/GUI/menu2.png");
	menu.setElementName("Menu1");
	menu.setElementVisible(false);
	gui.addElement(menu);

	std::cout << "efield init()\n";

	electricField.init();

	std::cout << "window binding\n";

	gui.bindWindow(window);

	std::cout << "end\n";
}


void Application::display() {
	static bool editTextBox = false;

	if(gui.isTextBoxAvaliable("textbox1")) {
		if(GUI::isKeyPressedb) {
			static std::string number = "";
				
			int max = 3;

			if(gui.isKeyPressed(GLFW_KEY_1) && number.size() < max)
				number += "1";	
			else if(gui.isKeyPressed(GLFW_KEY_2) && number.size() < max)
				number += "2";	
			else if(gui.isKeyPressed(GLFW_KEY_3) && number.size() < max)
				number += "3";	
			else if(gui.isKeyPressed(GLFW_KEY_4) && number.size() < max)
				number += "4";
			else if(gui.isKeyPressed(GLFW_KEY_5) && number.size() < max)
				number += "5";
			else if(gui.isKeyPressed(GLFW_KEY_6) && number.size() < max)
				number += "6";
			else if(gui.isKeyPressed(GLFW_KEY_7) && number.size() < max)
				number += "7";
			else if(gui.isKeyPressed(GLFW_KEY_8) && number.size() < max)
				number += "8";
			else if(gui.isKeyPressed(GLFW_KEY_9) && number.size() < max)
				number += "9";
			else if(gui.isKeyPressed(GLFW_KEY_0) && number.size() < max)
				number += "0";
			else if(gui.isKeyPressed(GLFW_KEY_MINUS) && number.size() < max)
				number += "-";
			else if(gui.isKeyPressed(GLFW_KEY_BACKSPACE)) {
				number = number.substr(0, number.length() - 1);
			}
				
			gui.setTextBoxText("1", number);

			std::istringstream sbuffer(number);
			sbuffer >> chargeValue;
		}
	}


	if(gui.isButtonPressed("Button1")) {
		mode = EDIT_ADD;
		isUpdated = true;
		return;
	}
	if(gui.isButtonPressed("Button2")) {
		mode = EDIT_MOVE;
		isUpdated = true;
		return;
	}
	if(gui.isButtonPressed("Button3")) {
		mode = EDIT_DELETE;
		isUpdated = true;
		return;
	}
	if(gui.isButtonPressed("Button4")) {
		static bool isVisible = false;
		gui.setVisibility("Menu1", !isVisible);
		isVisible = !isVisible;
	}

	if(isUpdated) {
		electricField.clear();
		for(Charge& ch : charges)
			electricField.addCharge(ch.getCharge(), ch.getPosition());
		electricField.createLines(true, true);
		isUpdated = false;
	}

	background.draw();
	electricField.drawLines(true);
	gui.display();
}
void Application::editMode_add() {
	gui.setCursor(GUI_Cursor::NONE);

	if(gui.isButtonPressed("Button1")) {
		mode = DISPLAY;
			
		background.draw();
		electricField.drawSprites();	
		gui.display();
			
		return;
	}
	if(gui.isButtonPressed("Button2")) {
		mode = EDIT_MOVE;
		isUpdated = true;
		return;
	}
	if(GUI::_mouse_right_button_pressed) {
		mode = DISPLAY;

		background.draw();
		electricField.drawSprites();	
		gui.display();

		return;
	}
	if(gui.isButtonPressed("Button4")) {
		mode = DISPLAY;
			
		background.draw();
		electricField.drawSprites();	
		gui.display();
			
		return;
	}

	electricField.clear();

	for(Charge& ch : charges)
		electricField.addCharge(ch.getCharge(), ch.getPosition());

	Charge ch(chargeValue, gui.getMousePosition());
	electricField.addCharge(ch.getCharge(), ch.getPosition());

	if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3) {
		mode = DISPLAY;
		charges.push_back(ch);
		return;
	}

	background.draw();
	electricField.drawSprites();	
	gui.display();
}
void Application::editMode_move() {

	gui.setCursor(GUI_Cursor::HAND);

	if(gui.isButtonPressed("Button1")) 
		editMode_add();
	if(gui.isButtonPressed("Button2")) {
		mode = DISPLAY;
		
		background.draw();
		electricField.drawSprites();	
		gui.display();
		
		return;
	}
	if(gui.isButtonPressed("Button4")) {
		
	}

	static bool isFinding = true;
	static glm::vec2 startPosition;
	static Charge* charge;

	if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3 && isFinding) {
		glm::vec2 mousePos = gui.getMousePosition();

		charge = getCharge(mousePos);

		if(charge == nullptr) {
			mode = DISPLAY;
			return;
		}
		else {
			isFinding = false;
			startPosition = charge->getPosition();
			glfwSetTime(0.0);
		}
	}

	if(!isFinding) {
		charge->setPosition(gui.getMousePosition());
		electricField.clear();

		for(Charge& ch : charges)
			electricField.addCharge(ch.getCharge(), ch.getPosition());

		if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3) {
			mode = DISPLAY;
			isFinding = true;
			return;
		}
		if(GUI::_mouse_right_button_pressed) {
			mode = DISPLAY;
	
			background.draw();
			electricField.drawSprites();	
			gui.display();
	
			charge->setPosition(startPosition);
	
			return;
		}
	}
	

	background.draw();
	electricField.drawSprites();	
	gui.display();
}
void Application::editMode_delete() {
	gui.setCursor(GUI_Cursor::ARROW);
	
	if(gui.isButtonPressed("Button1")) {
		mode = DISPLAY;
				
		background.draw();
		electricField.drawSprites();	
		gui.display();
				
		return;
	}
	if(gui.isButtonPressed("Button2")) {
		mode = EDIT_MOVE;
		isUpdated = true;
		return;
	}
	if(GUI::_mouse_right_button_pressed) {
		mode = DISPLAY;
	
		background.draw();
		electricField.drawSprites();	
		gui.display();
	
		return;
	}
	if(gui.isButtonPressed("Button4")) {
		mode = DISPLAY;
		return;
	}
	
	if(GUI::_mouse_button_pressed && glfwGetTime() > 0.3) {
		glm::vec2 mousePos = gui.getMousePosition();
		
		Charge* charge = getCharge(mousePos);
		
		if(charge == nullptr) {
			mode = DISPLAY;
			return;
		}
		else {
			std::vector<Charge> charges2;
			for(int i = 0, j = 0; i < charges.size(); i++) {
				if(areEqual(charges[i].getPosition(), charge->getPosition())) {
					continue;
				}
				charges2.push_back(charges[i]);
			}

			charges.clear();
			charges = charges2;

			mode = DISPLAY;
			return;
		}
	}
	if(GUI::_mouse_right_button_pressed) {
		mode = DISPLAY;
		return;
	}

	background.draw();
	electricField.drawSprites();	
	gui.display();
				
	return;
}



void Application::shutdown() {

	std::cout << "1\n";
	
	delete dinamicObject;
	std::cout << "1\n";
	gui.unbind();

	std::cout << "1\n";

	glfwDestroyWindow(window);
	std::cout << "1\n";
	glfwTerminate();
	std::cout << "1\n";
}
GLFWwindow* Application::getWindow() const { 
	return window;
}
Application::Mode Application::getMode() {
	return mode;
}

Charge* Application::getCharge(glm::vec2 pos) {
	for(int i = 0; i < charges.size(); i++) {
		Circle border { charges[i].getPosition(), 0.05 };

		if(border.isInCircle(pos))
			return &charges[i];
	}
	return nullptr;
}