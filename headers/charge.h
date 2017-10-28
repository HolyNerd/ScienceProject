////////////////////////////////////////////////////////////////
// Class Charge contains position and value of charge at position
// in space. Calculates magnitude and direction of electric field,
// that creates. Also contains field lines
////////////////////////////////////////////////////////////////

#ifndef CHARGE_H
#define CHARGE_H

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>

#include <line.h>

class Charge {
public:
	// Constructors
	Charge();
	Charge(GLfloat value, glm::vec2 position);
	~Charge();

	// Return electric field, that creats this charge
	// at point pos
	const glm::vec2 getElectricField(const glm::vec2& pos) const;
	
	// Returns position of charge
	const glm::vec2& getPosition() const;
	void setPosition(glm::vec2 newPosition);
	// Returns value of charge
	const GLfloat& getCharge() const;

	std::vector<Line>& getFieldLines();
private:
	GLfloat Q;
	glm::vec2 position;

	std::vector<Line> fieldLines;
};

#endif
