#pragma once

#include "matrix.h"
#include "vector.h"
#include "quaternion.h"

#define EULER false
#define QUATERNION true

class Camera
{
	float yRot = 0, xRot = 0;
	vec3 s, v, u;
	vec3 eye, center, up;
	qtrn orientation;
	mat4 rotationMatrix;
public:
	mat4 ViewMatrix = mat4::identityMatrix();
	mat4 originalMatrix;
	Camera();
	Camera(vec3 eye, vec3 center, vec3 up);
	void move(float xAngleOffset, float yAngleOffset, float depth);
	void updateQuaternionAndView(float x, float y);
	void updateQuaternionAndView(float depthOffSet);
	~Camera();
};

