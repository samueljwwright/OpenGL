#include "Object.h"

Object::Object() {
	//DELETE DUPLICATIONS
	vertexData = {

	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,

	-0.5f, -0.5f, 1.0f,
	0.5f, -0.5f, 1.0f,
	0.5f, 0.5f, 1.0f,
	-0.5f, 0.5f, 1.0f,

	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 1.0f,

	};

	 indexData = {
		//front
		0, 1, 2,
		2, 3, 0,
		//right
		2, 1, 5,
		2, 6, 5,
		//top
		8, 9, 10,
		9, 11, 10
	};

}