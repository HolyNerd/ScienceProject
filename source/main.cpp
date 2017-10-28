
#define GLEW_STATIC


#include <GL/glew.h>
#include <GL/glfw3.h>

#include <iostream>
#include <application.h>

int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(900, 900, "OpenGL: Electric Field", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	
	glewInit();


	Application app(window);
	app.init();
	

	Application::Mode mode;

	while(!glfwWindowShouldClose(window)) {
		mode = app.getMode();

		if(mode == Application::DISPLAY)
			app.display();
		else if(mode == Application::EDIT_ADD)
			app.editMode_add();
		else if(mode == Application::EDIT_MOVE)
			app.editMode_move();
		else if(mode == Application::EDIT_DELETE)
			app.editMode_delete();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	app.shutdown();

	return 0;
}
