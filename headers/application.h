
#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <glm/ext.hpp>

#include <sprite.h>
#include <shader.h>
#include <electricField.h>
#include <GUI.h>
#include <textbox.h>
#include <GUI_Text.h>
#include <menu.h>

class Application {
public:
	enum Mode { DISPLAY, EDIT_ADD, EDIT_MOVE, EDIT_DELETE };

	Application(GLFWwindow*);
	~Application();

	void init();

	Charge* getCharge(glm::vec2);

	void editMode_add();
	void editMode_move();
	void editMode_delete();

	void display();

	void shutdown();

	Mode getMode();
private:
	ElectricField electricField;
public: GLFWwindow* getWindow() const;
private: 
	Mode mode;

	bool isUpdated;

	GLFWwindow* window;
	GUI gui;
	
	Sprite background;

	std::vector<Charge> charges;
	Charge* dinamicObject;

	int chargeValue;
};

#endif