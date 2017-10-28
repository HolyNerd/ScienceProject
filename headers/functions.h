#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/vec2.hpp>

const bool areEqual (
	const glm::vec2& vecA, 
	const glm::vec2& vecB
);

const bool isNear (
	const glm::vec2& pos,
	const glm::vec2& target,
	const GLfloat& radius
);

const glm::vec2 getPerpendicular(const glm::vec2& v);


#endif