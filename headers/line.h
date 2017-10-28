///////////////////////////////////////////////////////////////////////
// Line - class, that contains set of points, and shader which draw line strip,
//				using control points 
///////////////////////////////////////////////////////////////////////

#ifndef LINE_H
#define LINE_H

// STD
#include <vector>
#include <iostream>
// OpenGL
#include <GL/glew.h>
// GLM
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
// My Libs 
#include <shader.h>
#include <functions.h>

class Line {
public:
	// Constructors
	Line();
	Line(glm::vec2 startPoint);
	Line(const Line&);
	~Line();

	// Get Methods
	const glm::vec2& getPoint(const int& i) const;
	const int getSize() const;

	const bool isIntersects (
		const int& 
		startPoint, 
		const int& endPoint, 
		const Line& rhs
	) const;

	// Set Methods
	void addPoint(glm::vec2 point);
	void setColor(glm::vec4 newColor);
	
	// Methods
	void clear(); // Delete all points, except first one
	void setShader(Shader);
	void updateBuffer();
	void draw();

	// Operators overloading (Comparing distance of liens' first and last points)
	// This needed for sorting lines
	bool operator==(const Line& rhs);
	bool operator!=(const Line& rhs);
	bool operator>(const Line& rhs);
	bool operator<(const Line& rhs);
	bool operator>=(const Line& rhs);
	bool operator<=(const Line& rhs);
	
private:
	// Points, structing the line
	std::vector<glm::vec2> controlPoints;

	// Lets think, what is this
	glm::vec4 lineColor;

	Shader* shader;
	GLuint* buffers;
	GLuint vao;

	enum buffersIDs { positionBuffer, colorBuffer, numBuffers };

	const Shader getShader() const;
};

#endif