#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
Sprite::Sprite()
{
	_vboID = 0; //start this object to 0 always.
}
Sprite::~Sprite() 
{
	//free vertex buffer
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	 

	//generate buffer if hasn't been generated
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);//generates a new buffer by passing by refference this id.
	}

	Vertex vertexData[6]; //array of floats; 2 because x and y coords; 6 because a square has 6 vertices (because it's made of 2 triangles)
	
	//first triangle
	
	//topright corner
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	//topleft corner 
	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	//bottomleft corner
	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//second triangle

	//bottomleft
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	//botright corner 
	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y ;

	//topright corner
	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;


	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);//tell that this buffer shouyld be active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//we upload data

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind buffer afterwards, akin to closing a file.
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);//tell that this is active.

	glEnableVertexAttribArray(0);//sending one array of positions, no additional info, no ligtning no nothing
	
	//number of elements (x and y) so 2
	//this is position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));//telling that we want to draw from the start, sometimes that's not the case
	//color, normalize converts from 0 to 1
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	glDrawArrays(GL_TRIANGLES, 0, 6);//to draw triangles but there's also option to do points, quads etc.
		//6 vertices

	glDisableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}