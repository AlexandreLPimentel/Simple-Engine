#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector.h>
#include <matrix.h>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

struct qtrn
{
	friend class qrtnTest;
private:
	float t, x, y, z;
public:
	const float qThreshold = (float)1.0e-5;
	qtrn();
	qtrn(float t, float x, float y, float z);
	~qtrn();
	const qtrn operator=(qtrn q);
	static const qtrn qFromAngleAxis(float theta, vec4 axis);
	static const void qToAngleAxis(const qtrn& q, float& theta, vec4& axis);
	static const void qClean(qtrn& q);
	static const float qQuadrance(const qtrn& q);
	static const float qNorm(const qtrn& q);
	static const qtrn qNormalize(const qtrn& q);
	static const qtrn qConjugate(const qtrn& q);
	static const qtrn qInverse(const qtrn& q);
	static const qtrn qAdd(const qtrn& q0, const qtrn& q1);
	static const qtrn qMultiply(const qtrn& q, const float s);
	static const qtrn qMultiply(const qtrn& q0, const qtrn& q1);
	static const void qGLMatrix(const qtrn& q, mat4* matrix);
	static const qtrn qLerp(const qtrn& q0, const qtrn& q1, float k);
	static const qtrn qSlerp(const qtrn& q0, const qtrn& q1, float k);
	const mat3 qToRotationMatrix();
	static const qtrn mToQuaternion(mat4& m);
	static const bool qEqual(const qtrn& q0, const qtrn& q1);
	static const void qPrint(const std::string& s, const qtrn& q);
	static const void qPrintAngleAxis(const std::string& s, const qtrn& q);

};

class qtrnTest {
public:
	void qtest1();
	void qtest2();
	void qtest3();
	void qtest4();
	void qtest5();
	void qtest6();
};
