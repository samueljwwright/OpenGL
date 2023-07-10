#include "Object.h"

Object::Object() {
	vertexData = {
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.5f, 0.5f,
	-0.5f, 0.5f
	};

	 indexData = {
		0, 1, 2,
		2, 3, 0

	};

}