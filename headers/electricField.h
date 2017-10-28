
#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <sprite.h>
#include <charge.h>
#include <shader.h>
#include <line.h>
#include <range.h>
#include <functions.h>

class ElectricField {
public:
	ElectricField();

	void init();
	void clear();

	void addCharge(const GLfloat& charge, const glm::vec2& pos);

	void createLines(bool createForceLines, bool createEquipotential);
	void drawLines(bool drawLines);

	void drawSprites();

	const glm::vec2 getNetElectricField(const glm::vec2& pos) const;
	const GLfloat getNetPotential(const glm::vec2& pos) const;

private:

	std::vector<Charge> charges;
	std::vector<Circle> chargesBorders;
	std::vector<Line> equipotentialLines;
	std::vector<Sprite> chargesSprites;

	GLfloat stride;

	Shader lineShader;

private:
	void setLinesStartPoints(Charge&);

	void genLine(Line&, const bool isPositive);
	void genField(Charge&);

	void genPotential(const Line& line, const GLfloat& charge);
	void genPotential(const glm::vec2& point);

	int getNextPoint(const Line& line, int i, GLfloat voltage);

private:
	Sprite posChargeSprite;
	Sprite negChargeSprite;
};

#endif