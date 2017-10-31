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

	cout << "Current mode: EULER" << endl;
	mode = EULER;

	rotationMatrix = mat4::identityMatrix();
	orientation = qtrn(1, 0, 0, 0);

	originalMatrix = mat4::lookAt(eye, center, up);
	ViewMatrix = mat4::lookAt(eye, center, up);
}

void Camera::changeMode() {
	mode = !mode;
	if (mode == EULER) {
		updateRotationAndView(xRot, yRot);
	}
	else {
		updateQuaternionAndView(0, 0);
	}
	cout << "Current mode: " << (mode == EULER ? "EULER" : "QUATERNION") << endl;
}

void Camera::move(float x, float y, float z, float xAngleOffset, float yAngleOffset)
{
	bool updateView = false;

	if (abs(x) > DBL_EPSILON || abs(y) > DBL_EPSILON) {

		if (mode == QUATERNION) {
			updateQuaternionAndView(x, y);
		}
		else {
			xRot += x;
			yRot += y;
			//new
			updateRotationAndView(xRot, yRot);
			//old
			//center += x * s;
			//eye += x * s;
			//ViewMatrix = mat4::lookAt(eye, center, up);
		}
	}
	if (abs(y) > DBL_EPSILON) {
		//old
		//eye += y * up;
		//center += y * up;

		//ViewMatrix = mat4::lookAt(eye, center, up);
	}
	if (abs(z) > DBL_EPSILON) {
		//old
		//center += z * v;
		//eye += z * v;

		//ViewMatrix = mat4::lookAt(eye, center, up);
	}
	/*if (xAngleOffset > DBL_EPSILON || xAngleOffset < -DBL_EPSILON) {

		v = v.rodrigues(up, xAngleOffset / 10);

		v.normalize();
		center = eye + v;
		s = v.cross(up);
		s.normalize();

		ViewMatrix = mat4::lookAt(eye, center, up);
	}
	if (yAngleOffset > DBL_EPSILON || yAngleOffset < -DBL_EPSILON) {

		v = v.rodrigues(s, yAngleOffset / 10);

		v.normalize();
		center = eye + v;
		up = s.cross(v);
		up.normalize();

		ViewMatrix = mat4::lookAt(eye, center, up);
	}*/
}

void Camera::updateQuaternionAndView(float x, float y) {

	if (x != 0 || y != 0) {
		qtrn qPitch = qtrn::qFromAngleAxis(y, vec3(1, 0, 0));
		qtrn qYaw = qtrn::qFromAngleAxis(x, vec3(0, 1, 0));

		orientation = qtrn::qMultiply(qtrn::qMultiply(qPitch, qYaw), orientation);
		orientation = qtrn::qNormalize(orientation);
	}
	mat4 rotate;
	qtrn::qGLMatrix(orientation, &rotate);
	ViewMatrix = originalMatrix * rotate;
}

void Camera::updateRotationAndView(float x, float y) {
	if (x != 0 || y != 0) {
		rotationMatrix = mat4::xRotationMatrix(y);
		rotationMatrix *= mat4::yRotationMatrix(x);
	}
	ViewMatrix = originalMatrix * rotationMatrix;
}

Camera::~Camera()
{
}
