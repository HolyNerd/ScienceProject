#include <functions.h>

#include <range.h>
const bool isNear (
	const glm::vec2& pos,
	const glm::vec2& target,
	const GLfloat& radius
) {
	Circle c;
	c.pos = pos;
	c.radius = radius;
	
	return c.isInCircle(target);
}

const bool areEqual (
	const glm::vec2& vecA, 
	const glm::vec2& vecB
) {
	const double epsilion = 0.0001;
	return fabs(vecA[0] -vecB[0]) < epsilion   
 		&& fabs(vecA[1] -vecB[1]) < epsilion;
}

const glm::vec2 getPerpendicular(const glm::vec2& v) {
	glm::vec2 perp(-v.y, v.x);
	return perp;
}
