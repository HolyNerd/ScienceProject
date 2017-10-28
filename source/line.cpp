
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <line.h>
#include <range.h>

Line::Line() { 
	buffers = new GLuint[numBuffers];
	shader = new Shader();
	lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0);

	glCreateBuffers(numBuffers, buffers);
	glCreateVertexArrays(1, &vao);
}

Line::Line(glm::vec2 startPoint) { 
	buffers = new GLuint[numBuffers];
	shader = new Shader();
	lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0);

	glCreateBuffers(numBuffers, buffers);
	glCreateVertexArrays(1, &vao);

	controlPoints.push_back(startPoint);
}

Line::Line(const Line& rhs) { 
	buffers = new GLuint[numBuffers];
	shader = new Shader();
	lineColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0);

	glCreateBuffers(numBuffers, buffers);
	glCreateVertexArrays(1, &vao);

	// Copies values from input Line
	controlPoints = rhs.controlPoints;

	shader->shaderInfo(rhs.getShader().getFilePath());

	lineColor = rhs.lineColor;

	updateBuffer();
}

Line::~Line() {
	controlPoints.clear();
	glDeleteProgram(*shader);
	glDeleteBuffers(numBuffers, buffers);
	glDeleteVertexArrays(1, &vao);
}

const Shader Line::getShader() const {
	return *shader;
}
const glm::vec2& Line::getPoint(const int& i) const {
	return controlPoints[i];
}
const int Line::getSize() const {
	return controlPoints.size();
}
const bool Line::isIntersects (
	const int& startPoint,
	const int& endPoint,
	const Line& rhs
) const {
	for(int i = startPoint; i < endPoint; i++) {
		const glm::vec2& currPoint = controlPoints[i];

		for(int p = 0; p < rhs.getSize(); p++) 
			if(isNear(currPoint, rhs.getPoint(p), 0.001)) 
				return true;
	}
	return false;
}

void Line::addPoint(glm::vec2 point) {
	controlPoints.push_back(point);
}
void Line::setColor(glm::vec4 newColor) {
	lineColor = newColor;
}

void Line::clear() {
	glm::vec2 startPoint = controlPoints[0];
	controlPoints.clear();
	controlPoints.push_back(startPoint);
}
void Line::setShader(Shader newShader) {
	//delete this->shader;
	this->shader = new Shader(newShader);
}
void Line::updateBuffer() {
	// If buffer are not created - create them 
//	for(int i = 0; i < numBuffers; i++) 
//		if(glIsBuffer(buffers[i]) == GL_FALSE) {
//			glCreateBuffers(1, &buffers[i]); 
	//	}

//	if(glIsVertexArray(vao) == GL_FALSE) 
//		glCreateVertexArrays(1, &vao); 


	// Bind VAO
	glBindVertexArray(vao);
	
	// Set Position Buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[positionBuffer]);
	glBufferData(
		GL_ARRAY_BUFFER, 
		controlPoints.size() * sizeof(glm::vec2), 
		controlPoints.data(), 
		GL_STATIC_DRAW
	);

	// Bind bao and shader attrib
	glVertexArrayVertexBuffer(vao, 0, buffers[positionBuffer], 0, 
		sizeof(GLfloat)*2);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	glEnableVertexAttribArray(0);


	// Set Color Buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[colorBuffer]);

	// Create color
	GLfloat color[4];
	color[0] = lineColor.r;
	color[1] = lineColor.g;
	color[2] = lineColor.b;
	color[3] = lineColor.a;

	// Fetch buffer data
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(color), 
		color, 
		GL_STATIC_DRAW
	);

	// Bind bao and shader attrib
	glVertexArrayVertexBuffer(vao, 1, buffers[colorBuffer], 0, 0);
	glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
	glEnableVertexAttribArray(1);

	// Unbind all buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Line::draw() {
	glBindVertexArray(vao);
	glUseProgram(*shader);
	
	glDrawArrays(GL_LINE_STRIP, 0, controlPoints.size());
	glBindVertexArray(0);
}


bool Line::operator==(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) == glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator!=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) != glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator>(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) > glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator<(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) < glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator>=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) >= glm::length(rhsLength))
		return true;
	return false;
}
bool Line::operator<=(const Line& rhs) {
	glm::vec2 lhsLength = controlPoints[controlPoints.size()-1]-controlPoints[0];
	glm::vec2 rhsLength = rhs.controlPoints[rhs.controlPoints.size()-1]-rhs.controlPoints[0];

	if(glm::length(lhsLength) <= glm::length(rhsLength))
		return true;
	return false;
}