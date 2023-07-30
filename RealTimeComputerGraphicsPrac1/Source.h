#ifndef Source_H_
#define Source_H_

#include "Object.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Shader.h"
#include "ObjLoader.h"
#include <windows.h>

//Keycode aliases
constexpr int W_KEY = 0x57;
constexpr int S_KEY = 0x53;
constexpr int A_KEY = 0x41;
constexpr int D_KEY = 0x44;
constexpr int SHIFT_KEY = 0x10;
constexpr int SPACE_KEY = 0x20;
constexpr int PRESSED_BIT_FLAG = 0x8000; //determines if key is currently pressed

struct DirectionalLight {
	glm::vec4 lightColour = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 lightPosition = { 2.0f, -2.0f, 2.0f, 1.0f };
};





class Source 
{
private:
	void input();
	void renderObject(unsigned int modelMatrixLocation, glm::mat4 objectTransfromReference, int indexDataSize);
	void setObject(Object* object, glm::vec3 position, glm::vec3 rotation);
	glm::mat4 viewMatrix;
	float deltaTime;
	
public:
	int WindowInit();
};

#endif // !1
