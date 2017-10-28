
#include <sprite.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Sprite::Sprite() {

} 

Sprite::Sprite(const Sprite& rhs) {
	init();
	
	for(int i = 0; i < 4; i++) {
		center_coordVectors[i] = rhs.center_coordVectors[i];
		coords[i] = rhs.coords[i];
	
		texCoords[i] = rhs.texCoords[i];
	}

	shader = rhs.shader;
	
	texturePath = rhs.texturePath;

	setTexture(texturePath);
}

Sprite& Sprite::operator=(const Sprite& rhs) {
	init();
	
	for(int i = 0; i < 4; i++) {
		center_coordVectors[i] = rhs.center_coordVectors[i];
		coords[i] = rhs.coords[i];
	
		texCoords[i] = rhs.texCoords[i];
	}

	shader = rhs.shader;
	
	texturePath = rhs.texturePath;

	setTexture(texturePath);

	return *this;
}

Sprite::~Sprite() {
	glDeleteBuffers(numBuffers, buffers);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);
	glDeleteProgram(shader);

	delete[] buffers;
}

void Sprite::init() {
	buffers = new GLuint[numBuffers];
	glCreateBuffers(numBuffers, buffers);
	glGenTextures(1, &texture);
	glCreateVertexArrays(1, &vao);

	texCoords[0] = glm::vec2(0.0, 1.0);
	texCoords[1] = glm::vec2(1.0, 1.0);
	texCoords[2] = glm::vec2(1.0, 0.0);
	texCoords[3] = glm::vec2(0.0, 0.0);
}


const GLfloat Sprite::getWidth() {
	GLfloat width = 0;
	width = coords[1].x - center.x;
	return width;
}

void Sprite::setRect(glm::vec2 setCenter, GLfloat width, GLfloat height) {

	center = setCenter;

	coords[0].x = center.x - width/2;
	coords[0].y = center.y - height/2;

	coords[1].x = center.x + width/2;
	coords[1].y = center.y - height/2;

	coords[2].x = center.x + width/2;
	coords[2].y = center.y + height/2;

	coords[3].x = center.x - width/2;
	coords[3].y = center.y + height/2;

	for(int i = 0; i < 4; i++) {
		center_coordVectors[i] = coords[i] - center;
	}
}

void Sprite::setShader(const char* fileName) {
	shader.shaderInfo(fileName);
}

void Sprite::setTexture(const char* fileName) {
	texturePath = fileName;
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, STBI_rgb_alpha);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}	
	else {
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
}

void Sprite::setTextureCoord(glm::vec2 coord[4]) {
	for(int i = 0; i < 4; i++) 
		texCoords[i] = coord[i];
}

void Sprite::setPosition(glm::vec2 newPosition) {
	center = newPosition;

	for(int i = 0; i < 4; i++)
		coords[i] = center + center_coordVectors[i];
}

void Sprite::rotate(GLfloat angle) {
	glm::mat2 rotMat (
		glm::vec2(cos(angle), -sin(angle)),
		glm::vec2(sin(angle), cos(angle))
	);
	for(int i = 0; i < 4; i++) 
		center_coordVectors[i] = center_coordVectors[i] * rotMat;

	for(int i = 0; i < 4; i++)
		coords[i] = center + center_coordVectors[i];
}

void Sprite::update() {

	// Vertecies positions
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[vertexBuffer]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*4, coords, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vao, 0, buffers[vertexBuffer], 0, sizeof(GLfloat)*2);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexAttribBinding(0, 0);
	glEnableVertexAttribArray(0);
	
	glm::vec2 cords[4];

	for (int i = 0; i < 4; i++) {
		cords[i] = texCoords[i];
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffers[texCords]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*4, cords, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vao, 1, buffers[texCords], 0, sizeof(GLfloat)*2);
	glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	

}

void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shader);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}