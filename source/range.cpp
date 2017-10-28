#include <range.h>

bool Range::isIn(int i) {
	if((i < end && i > start) || (i > end && i < start) ) { 
		return true;
	}
	else {
		return false;
	}
}

bool Area::isInArea(glm::vec2 point) {	
	if(point.x > top_left.x && point.x < down_right.x 
	&& point.y > down_right.y && point.y < top_left.y)
		return true;
	return false;
}

bool Circle::isInCircle(glm::vec2 p) {
	glm::vec2 r = p - pos;
	if(glm::length(r) >= radius)
		return false;
	return true;
}