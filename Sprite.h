#pragma once
#include <GL/glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height); //we assume sprite is a square

	void draw();

private:
	float _x, _y, _width, _height;
	GLuint _vboID;//vertex buffer id; GLuint is a guaruanteed unsigned 32 bit

};

