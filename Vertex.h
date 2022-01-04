#pragma once

struct Vertex {
	struct Position {
		float x;
		float y;
	} position; //vertex.position.x

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} color;
};
