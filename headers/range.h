
#ifndef RANGE_H
#define RANGE_H

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

struct Range {
	int start;
	int end;

	bool isIn(int i);
};

struct Area {
	glm::vec2 top_left;
	glm::vec2 down_right;
	bool isInArea(glm::vec2 point);
};

struct Circle {
	glm::vec2 pos;
	float radius;
	
	bool isInCircle(glm::vec2 p);
};

#endif