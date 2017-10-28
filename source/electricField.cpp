#define FORCE_LINES
#define EQUIPOTENTIAL

#include <electricField.h>

#include <iostream>
#include <math.h>

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
#include <glm/glm.hpp>

ElectricField::ElectricField() 
	: stride { 0.005f }, equipotentialLines(0)
{

}

void ElectricField::init() {
	lineShader.shaderInfo("Shaders/line");

//	Sprite posChargeSprite;
//	Sprite negChargeSprite;

	posChargeSprite.init();
	posChargeSprite.setShader("Shaders/charge");
	posChargeSprite.setRect(glm::vec2(0,0), 0.08f, 0.08f);
	posChargeSprite.setTexture("Media/charge_positive_02.png");

	negChargeSprite.init();
	negChargeSprite.setShader("Shaders/charge");
	negChargeSprite.setRect(glm::vec2(0,0), 0.08f, 0.08f);
	negChargeSprite.setTexture("Media/charge_neg_2.png");
}

const glm::vec2 ElectricField::getNetElectricField(const glm::vec2& pos) const {
	glm::vec2 netField;

	for(int i = 0; i < charges.size(); i++) {
		glm::vec2 eField = charges[i].getElectricField(pos);
		netField += eField;
	}
	return netField;
}
const GLfloat ElectricField::getNetPotential(const glm::vec2& pos) const {
	GLfloat sum = 0;
	for(int i = 0; i < charges.size(); i++) {
		glm::vec2 dist = pos - charges[i].getPosition();
		GLfloat r = glm::length(dist);
		GLfloat potential = charges[i].getCharge() * 90 / r ;
		sum += potential; 
	}
	return sum;
}

void ElectricField::addCharge(const GLfloat& charge, const glm::vec2& pos) {
	if(charge == 0)
		return;

	Charge c(charge, pos);
	charges.push_back(c);

	Circle border;
	border.pos = pos;
	border.radius = 0.01;

	chargesBorders.push_back(border);
}

// CLEAR_DRAW
void ElectricField::clear() {
	charges.clear();
	chargesBorders.clear();
	equipotentialLines.clear();
	chargesSprites.clear();
}
void ElectricField::drawLines(bool drawLines) {

	glLineWidth(1.0f);
	if(drawLines)
		for(int i = 0; i < equipotentialLines.size(); i++)
			equipotentialLines[i].draw();
	

	// Draw force lines
	glLineWidth(1.0f);
	if(drawLines)
		for(Charge& ch : charges) {
			for(int i = 0; i < ch.getFieldLines().size(); i++) {
				ch.getFieldLines()[i].draw();
			}
		}	
	drawSprites();
	//for(int i = 0; i < chargesSprites.size(); i++) {
	//	chargesSprites[i].update();
	//	chargesSprites[i].draw();
	//}
}

// GENERAL CREATE LINES METHOD
void ElectricField::createLines(bool createForceLines, bool createEquipotential) {
	// Draw charges sprites
	//for(Charge& ch : charges) {
	//	Sprite newChargeSprite;

	//	newChargeSprite.init();
	//	newChargeSprite.setShader("/home/holynerd/Desktop/Projects/ElectricField/Shaders/charge");
	//	newChargeSprite.setRect(ch.getPosition(), 0.1f, 0.1f);

	//	if(ch.getCharge() > 0)
	//		newChargeSprite.setTexture("/home/holynerd/Desktop/Projects/ElectricField/Media/ChargePos.png");
	//	else
	//		newChargeSprite.setTexture("/home/holynerd/Desktop/Projects/ElectricField/Media/ChargeNeg.png");

	//	chargesSprites.push_back(newChargeSprite);
	//}

	for(int c = 0; c < charges.size(); c++) {

		if(createForceLines) {
			setLinesStartPoints(charges[c]);
			genField(charges[c]);	
		}
		if(createEquipotential) {
			std::vector<Line> chargeLines = charges[c].getFieldLines();
			std::sort(chargeLines.begin(), chargeLines.end());
			genPotential(chargeLines[chargeLines.size()-1], charges[c].getCharge());
		}

	}
}
void ElectricField::drawSprites() {
	for(int i = 0; i < charges.size(); i++) {
		if(charges[i].getCharge() < 0) {
			negChargeSprite.setPosition(charges[i].getPosition());
			negChargeSprite.update();
			negChargeSprite.draw();
			continue;
		}
		posChargeSprite.setPosition(charges[i].getPosition());
		posChargeSprite.update();
		posChargeSprite.draw();
	}
}

// FORCE LINES
void ElectricField::genField(Charge& charge) {

	for(int i = 0; i < charge.getFieldLines().size(); i++) {

		if(charge.getCharge() < 0) 
			genLine(charge.getFieldLines()[i], false);
		else
			genLine(charge.getFieldLines()[i], true);
		
		charge.getFieldLines()[i].updateBuffer();
	}

}
void ElectricField::genLine(Line& line, bool isPositive) {
	bool drawNext = true;
	int p = 1;

	glm::vec2 nextPointPos;
	glm::vec2 prevPointPos;
	glm::vec2 netField;
	while(p < 4000) {

		// Get previous point position
		prevPointPos = line.getPoint(p-1);

		// Get net electric field vector of previous point
		netField = getNetElectricField(prevPointPos);
		netField = glm::normalize(netField);

		// If charge is negative - invert vector
		if(!isPositive) 
			netField = netField * -1.0f;
		
		glm::vec2 nextNetField = getNetElectricField(prevPointPos + netField * stride);
		nextNetField = glm::normalize(nextNetField);

		

		if(!isPositive) 
			nextNetField = nextNetField * -1.0f;

		netField = (netField + nextNetField) / 2.0f;
		
		// Set next point position
		nextPointPos = prevPointPos + netField * stride;

				// If next ends on some charge - end line drawing
		for(Circle c : chargesBorders) 
			if(c.isInCircle(nextPointPos)) 
				return;

	// Check for next net electric field
		nextNetField = getNetElectricField(nextPointPos);
		nextNetField = glm::normalize(nextNetField);
		if(isPositive)
			nextNetField*=-1;
				
	// If next net electric field and current inverted are equil - then quit
		if(areEqual(nextNetField, netField)) {
			line.addPoint(nextPointPos);
			return;
		}

		// Add point to line
		line.addPoint(nextPointPos);

		// If point is out of screen - do not draw next point 
		if(abs(nextPointPos.x) >= 1 || abs(nextPointPos.y) >= 1)
			return; 

		// Increment point index
		p++;
	}
}
void ElectricField::setLinesStartPoints(Charge& ch) {
	// Get charge's position
	glm::vec2 pos = ch.getPosition();

	// Get lines amount and angle between them
	int n = 8 * abs(ch.getCharge());
	float a = 360.0f / n;
	a = glm::radians(a);
	glm::vec2 r(0.0f, 0.01f);
	glm::mat2 rotation (
		glm::vec2(cos(a),-sin(a)),
		glm::vec2(sin(a),cos(a))
	);

	for(int i = 0; i < n; i++) {
		Line newLine(pos + r);

		glm::vec2 posr = pos + r;

		//newLine.setColor(glm::vec4(186.0 / 255.0f, 255.0 / 255.0f, 229.0 / 255.0, 1.0f));
		newLine.setColor(glm::vec4(125.0 / 255.0f, 125.0 / 255.0f, 125.0 / 255.0, 1.0f));
		newLine.setShader(lineShader);

		ch.getFieldLines().push_back(newLine); 
		r = r * rotation;
	}
}


// EQUIPOTENTIAL
void ElectricField::genPotential(const Line& line, const GLfloat& charge) {

	GLfloat voltage = 400.0f;
	GLfloat potential = getNetPotential(line.getPoint(1));

	int startPoint = equipotentialLines.size();

	int i = 2;
	while(i < line.getSize()) {
		GLfloat nextPotential = getNetPotential(line.getPoint(i));
		
		if(std::signbit(nextPotential) != std::signbit(potential))
			return;
		
		if(abs(potential - nextPotential) > voltage) {
			GLfloat dif = potential - nextPotential;
			for(int p2 = 0; p2 < startPoint; p2++) {
				GLfloat lPotential = getNetPotential(equipotentialLines[p2].getPoint(0));
				if(nextPotential + (voltage) > lPotential && nextPotential - (voltage) < lPotential) 
					if(line.isIntersects(i, line.getSize(), equipotentialLines[p2])) 
						return;
			}

			genPotential(line.getPoint(i));
			potential = nextPotential;
		}
		i++;
	}

}
void ElectricField::genPotential(const glm::vec2& point) {
	float stride = 0.001;

	Line line;
	line.addPoint(point);

	glm::vec2 newPointPos;
	glm::vec2 prevPointPos;
	glm::vec2 netField;
			
	glm::vec2 potentialDir;

	bool isNegative = std::signbit(getNetPotential(point));
	GLfloat netPotential = abs(getNetPotential(point)) / 1000.0;

	int i = 1;
	bool drawNext = true;
	while(i < 33000) {

		// Get previoius point
		prevPointPos = line.getPoint(i-1);

		// Find out electric field in previous point
		netField = getNetElectricField(prevPointPos);
		netField = glm::normalize(netField);

		// Potential vector direction - perpendicular of electric field at choosen point
		potentialDir = getPerpendicular(netField);

		// Find out electric field in next point
		netField = getNetElectricField(prevPointPos + potentialDir * stride);
		netField = glm::normalize(netField);

		// Final slope vector - average of two prev vectors 
		glm::vec2 slope = getPerpendicular(netField);
		slope = (potentialDir + slope) / 2.0f;

		// Set new point position
		newPointPos = prevPointPos + slope * stride;
		line.addPoint(newPointPos);


		if(i > 100 && isNear(point, newPointPos, stride*2)) {
			line.addPoint(point);
			break;
		}

		i++;
	}

	line.setShader(lineShader);
	if(isNegative)
		//line.setColor(glm::vec4(0.0 / 255.0f, 255.0 / 255.0f, 0.0 / 255.0, 0.2f * netPotential));
		line.setColor(glm::vec4(124.0 / 255.0f, 124.0 / 255.0f, 124.0 / 255.0, 0.2f * netPotential));
	else
		//line.setColor(glm::vec4(0.0 / 255.0f, 255.0 / 255.0f, 255.0 / 255.0, 0.2f * netPotential));
		line.setColor(glm::vec4(124.0 / 255.0f, 124.0 / 255.0f, 124.0 / 255.0, 0.2f * netPotential));
	

		line.updateBuffer();
	
	equipotentialLines.push_back(Line(line));
}
int ElectricField::getNextPoint(const Line& line, int i, GLfloat voltage) {
	GLfloat iPotential = getNetPotential(line.getPoint(i));
	GLfloat potential = 0;

	for(int p = i; p < line.getSize(); p++) {
		potential = getNetPotential(line.getPoint(p));
		if(iPotential - potential > voltage)
			return p;
		if(potential > iPotential)
			return -1;
	}
}

