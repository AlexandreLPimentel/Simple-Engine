#include "Camera.h"

Camera::Camera() {}

Camera::Camera(vec3 eye, vec3 center, vec3 up)
{
	v = center - eye;
	v.normalize();

	s = v.cross(up);
	s.normalize();

	u = s.cross(v);
	u.normalize();

	this->eye = vec3(eye);
	this->center = vec3(center);
	this->up = vec3(up);

	orientation = qtrn(1, 0, 0, 0);

	originalMatrix = mat4::lookAt(eye, center, up);
	ViewMatrix = originalMatrix;
}

void Camera::move(float xAngleOffset, float yAngleOffset, float depth)
{
	bool updateView = false;

	if (abs(depth) > DBL_EPSILON) {
		updateQuaternionAndView(depth * 0.05f);
	}
	if (abs(xAngleOffset) > DBL_EPSILON || abs(yAngleOffset) > DBL_EPSILON) {
		updateQuaternionAndView(xAngleOffset, yAngleOffset);
	}
}

void Camera::updateQuaternionAndView(float x, float y) {

	if (x != 0 || y != 0) {
		qtrn qPitch = qtrn::qFromAngleAxis(y, vec3(1, 0, 0));
		qtrn qYaw = qtrn::qFromAngleAxis(x, vec3(0, 1, 0));
		qtrn combined = qtrn::qMultiply(qPitch, qYaw);

		orientation = qtrn::qMultiply(combined.qNormalize(combined), orientation);
		orientation = qtrn::qNormalize(orientation);
	}
	mat4 rotate;
	qtrn::qGLMatrix(orientation, &rotate);
	ViewMatrix = originalMatrix * rotate;
}

void Camera::updateQuaternionAndView(float depthOffSet) {
	originalMatrix.setCoordinate(2, 3, originalMatrix.getCoordinate(2, 3) + depthOffSet);
	mat4 rotate;
	qtrn::qGLMatrix(orientation, &rotate);
	ViewMatrix = originalMatrix * rotate;
}

Camera::~Camera()
{
}
