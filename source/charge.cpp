
#include <charge.h>

Charge::Charge() { 
	Q = 0;
	position = glm::vec2(0.0f, 0.0f);
}
Charge::Charge(GLfloat charge, glm::vec2 pos) 
	: Q(charge), position(pos)
{ }

Charge::~Charge() {
	fieldLines.clear();
}

const glm::vec2& Charge::getPosition() const {
	return position;
}

void Charge::setPosition(glm::vec2 newPosition) {
	position = newPosition;
}

const GLfloat& Charge::getCharge() const {
	return Q;
}

const glm::vec2 Charge::getElectricField(const glm::vec2& pos) const {
	glm::vec2 unit = pos - position;
	GLfloat r = glm::length(unit);
	unit = glm::normalize(unit);

	GLfloat E = Q / pow(r, 2);

	glm::vec2 field = E * unit;

	return field;
}

std::vector<Line>& Charge::getFieldLines() {
	return fieldLines;
}
