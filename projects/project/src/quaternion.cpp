#include "quaternion.h"



qtrn::qtrn()
{
}


qtrn::qtrn(float t, float x, float y, float z)
{
	this->t = t;
	this->x = x;
	this->y = y;
	this->z = z;
}

qtrn::~qtrn()
{
}

const qtrn qtrn::operator=(qtrn q)
{
	t = q.t;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}



const qtrn qtrn::qFromAngleAxis(float theta, vec4 axis)
{
	vec4 axisn = vec4::normalize(axis);

	qtrn q;
	float a = theta * (float)DEGREES_TO_RADIANS;
	q.t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	q.x = axisn.data[0] * s;
	q.y = axisn.data[1] * s;
	q.z = axisn.data[2] * s;

	qClean(q);
	return qNormalize(q);
}

const void qtrn::qToAngleAxis(const qtrn& q, float& theta, vec4& axis)
{
	qtrn qn = qNormalize(q);
	theta = 2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn.t*qn.t);
	if (s < qn.qThreshold) {
		axis.data[0] = 1.0f;
		axis.data[1] = 0.0f;
		axis.data[2] = 0.0f;
		axis.data[3] = 1.0f;
	}
	else {
		axis.data[0] = qn.x / s;
		axis.data[1] = qn.y / s;
		axis.data[2] = qn.z / s;
		axis.data[3] = 1.0f;
	}
}

const void qtrn::qClean(qtrn& q)
{
	if (fabs(q.t) < q.qThreshold) q.t = 0.0f;
	if (fabs(q.x) < q.qThreshold) q.x = 0.0f;
	if (fabs(q.y) < q.qThreshold) q.y = 0.0f;
	if (fabs(q.z) < q.qThreshold) q.z = 0.0f;
}

const float qtrn::qQuadrance(const qtrn& q)
{
	return q.t*q.t + q.x*q.x + q.y*q.y + q.z*q.z;
}

const float qtrn::qNorm(const qtrn& q)
{
	return sqrt(qQuadrance(q));
}

const qtrn qtrn::qNormalize(const qtrn& q)
{
	float s = 1 / qNorm(q);
	return qMultiply(q, s);
}

const qtrn qtrn::qConjugate(const qtrn& q)
{
	qtrn qconj = { q.t, -q.x, -q.y, -q.z };
	return qconj;
}

const qtrn qtrn::qInverse(const qtrn& q)
{
	return qMultiply(qConjugate(q), 1.0f / qQuadrance(q));
}

const qtrn qtrn::qAdd(const qtrn& q0, const qtrn& q1)
{
	qtrn q;
	q.t = q0.t + q1.t;
	q.x = q0.x + q1.x;
	q.y = q0.y + q1.y;
	q.z = q0.z + q1.z;
	return q;
}

const qtrn qtrn::qMultiply(const qtrn& q, const float s)
{
	qtrn sq = qtrn();
	sq.t = s * q.t;
	sq.x = s * q.x;
	sq.y = s * q.y;
	sq.z = s * q.z;
	return sq;
}

const qtrn qtrn::qMultiply(const qtrn& q0, const qtrn& q1)
{
	qtrn q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

const void qtrn::qGLMatrix(const qtrn& q, mat4* matrix)
{
	qtrn qn = qNormalize(q);

	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	matrix->setCoordinate(0, 0, 1.0f - 2.0f * (yy + zz));
	matrix->setCoordinate(1, 0, 2.0f * (xy + zt));
	matrix->setCoordinate(2, 0, 2.0f * (xz - yt));
	matrix->setCoordinate(3, 0, 0.0f);

	matrix->setCoordinate(0, 1, 2.0f * (xy - zt));
	matrix->setCoordinate(1, 1, 1.0f - 2.0f * (xx + zz));
	matrix->setCoordinate(2, 1, 2.0f * (yz + xt));
	matrix->setCoordinate(3, 1, 0.0f);

	matrix->setCoordinate(0, 2, 2.0f * (xz + yt));
	matrix->setCoordinate(1, 2, 2.0f * (yz - xt));
	matrix->setCoordinate(2, 2, 1.0f - 2.0f * (xx + yy));
	matrix->setCoordinate(3, 2, 0.0f);

	matrix->setCoordinate(0, 3, 0.0f);
	matrix->setCoordinate(1, 3, 0.0f);
	matrix->setCoordinate(2, 3, 0.0f);
	matrix->setCoordinate(3, 3, 1.0f);

	matrix->clean();
}

const qtrn qtrn::qLerp(const qtrn& q0, const qtrn& q1, float k)
{
	float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	qtrn qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

const qtrn qtrn::qSlerp(const qtrn& q0, const qtrn& q1, float k)
{
	float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	qtrn qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

const mat3 qtrn::qToRotationMatrix()
{
	return mat3(
		1 - 2 * y*y - 2 * z*z, 2 * x*y - 2 * t*z, 2 * x*z + 2 * t*y,
		2 * x*y - 2 * t*z, 1 - 2 * x*x - 2 * z*z, 2 * y*z - 2 * t*x,
		2 * x*z - 2 * t*y, 2 * y*z + 2 * t*x, 1 - 2 * x*x - 2 * y*y);
}

//code from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
const qtrn qtrn::mToQuaternion(mat4 & m)
{
	float m00 = m.getCoordinate(0, 0);
	float m01 = m.getCoordinate(0, 1);
	float m02 = m.getCoordinate(0, 2);
	float m10 = m.getCoordinate(1, 0);
	float m11 = m.getCoordinate(1, 1);
	float m12 = m.getCoordinate(1, 2);
	float m20 = m.getCoordinate(2, 0);
	float m21 = m.getCoordinate(2, 1);
	float m22 = m.getCoordinate(2, 2);

	qtrn q;

	float tr = m00 + m11 + m22;

		if (tr > 0) {
			float S = sqrt(tr + 1.0) * 2; // S=4*qw 
			q.t = 0.25 * S;
			q.x = (m21 - m12) / S;
			q.y = (m02 - m20) / S;
			q.z = (m10 - m01) / S;
		}
		else if ((m00 > m11)&(m00 > m22)) {
			float S = sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx 
			q.t = (m21 - m12) / S;
			q.x = 0.25 * S;
			q.y = (m01 + m10) / S;
			q.z = (m02 + m20) / S;
		}
		else if (m11 > m22) {
			float S = sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
			q.t = (m02 - m20) / S;
			q.x = (m01 + m10) / S;
			q.y = 0.25 * S;
			q.z = (m12 + m21) / S;
		}
		else {
			float S = sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
			q.t = (m10 - m01) / S;
			q.x = (m02 + m20) / S;
			q.y = (m12 + m21) / S;
			q.z = 0.25 * S;
		}
	return q;
}

const bool qtrn::qEqual(const qtrn& q0, const qtrn& q1)
{
	return (fabs(q0.t - q1.t) < q0.qThreshold && fabs(q0.x - q1.x) < q0.qThreshold &&
		fabs(q0.y - q1.y) < q0.qThreshold && fabs(q0.z - q1.z) < q0.qThreshold);
}

const void qtrn::qPrint(const std::string& s, const qtrn& q)
{
	std::cout << s << " = (" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
}

const void qtrn::qPrintAngleAxis(const std::string& s, const qtrn& q)
{
	std::cout << s << " = [" << std::endl;

	float thetaf;
	vec4 axis_f;
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << "  angle = " << thetaf << std::endl;
	std::cout << axis_f << std::endl;
	std::cout << "]" << std::endl;
}

///////////////////////////////////////////////////////////////////////

#define HEADER(X) std::cout<<std::endl<<(X)<<std::endl<<std::endl;

void qtrnTest::qtest1()
{
	HEADER("TEST 1 : Rotation of 90 degrees about the y-axis")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qtrn::qFromAngleAxis(90.0f, axis);
	qtrn::qPrint("   q", q);

	qtrn vi = { 0.0f, 7.0f, 0.0f, 0.0f };
	qtrn::qPrint("  vi", vi);

	qtrn qe = { 0.0f, 0.0f, 0.0f, -7.0f };
	qtrn::qPrint("  qe", qe);

	qtrn qinv = qtrn::qInverse(q);
	qtrn::qClean(qinv);
	qtrn::qPrint("qinv", qinv);

	qtrn qf = qtrn::qMultiply(qtrn::qMultiply(q, vi), qinv);
	qtrn::qPrint("  qf", qf);

	assert(qtrn::qEqual(qf, qe));
}

void qtrnTest::qtest2()
{
	HEADER("TEST 2 : Rotation of 90 degrees about the y-axis with matrix")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qtrn::qFromAngleAxis(90.0f, axis);
	qtrn::qPrint(" q", q);

	vec4 vi = { 7.0f, 0.0f, 0.0f, 1.0f };
	std::cout << "vi " << vi << std::endl;

	vec4 ve = { 0.0f, 0.0f, -7.0f, 1.0f };
	std::cout << "ve " << ve << std::endl;

	mat4 m;
	qtrn::qGLMatrix(q, &m);
	std::cout << " M " << m << std::endl;

	vec4 vf = m * vi;
	std::cout << "vf " << vf << std::endl;

	assert(vf == ve);
}

void qtrnTest::qtest3()
{
	HEADER("TEST 3 : Yaw 900 = Roll 180 + Pitch 180")

		vec4 axis_x = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4 axis_y = { 0.0f, 1.0f, 0.0f, 1.0f };
	vec4 axis_z = { 0.0f, 0.0f, 1.0f, 1.0f };

	qtrn qyaw900 = qtrn::qFromAngleAxis(900.0f, axis_y);
	qtrn::qPrint("  qyaw900", qyaw900);

	qtrn qroll180 = qtrn::qFromAngleAxis(180.0f, axis_x);
	qtrn::qPrint(" qroll180", qroll180);
	qtrn qpitch180 = qtrn::qFromAngleAxis(180.0f, axis_z);
	qtrn::qPrint("qpitch180", qpitch180);
	qtrn qrp = qtrn::qMultiply(qpitch180, qroll180);
	qtrn::qPrint("      qrp", qrp);
	qtrn qpr = qtrn::qMultiply(qroll180, qpitch180);
	qtrn::qPrint("      qpr", qpr);

	qtrn qi = { 0.0f, 1.0f, 0.0f, 0.0f }; // x-axis
	qtrn::qPrint("       qi", qi);
	qtrn qe = { 0.0f, -1.0f, 0.0f, 0.0f };
	qtrn::qPrint("       qe", qe);

	qtrn qyaw900inv = qtrn::qInverse(qyaw900);
	qtrn qfy = qtrn::qMultiply(qtrn::qMultiply(qyaw900, qi), qyaw900inv);
	qtrn::qPrint("       qy", qfy);
	assert(qtrn::qEqual(qe, qfy));

	qtrn qrpinv = qtrn::qInverse(qrp);
	qtrn qfrp = qtrn::qMultiply(qtrn::qMultiply(qrp, qi), qrpinv);
	qtrn::qPrint("     qfrp", qfrp);
	assert(qtrn::qEqual(qe, qfrp));

	qtrn qprinv = qtrn::qInverse(qpr);
	qtrn qfpr = qtrn::qMultiply(qtrn::qMultiply(qpr, qi), qprinv);
	qtrn::qPrint("     qfpr", qfpr);
	assert(qtrn::qEqual(qe, qfpr));
}

void qtrnTest::qtest4()
{
	HEADER("TEST 4: Q <-> (angle, axis)")

		float thetai = 45.0f;
	vec4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q = qtrn::qFromAngleAxis(thetai, axis_i);
	std::cout << thetai << " ";
	std::cout << "axis_i " << axis_i << std::endl;

	float thetaf;
	vec4 axis_f;
	qtrn::qToAngleAxis(q, thetaf, axis_f);
	std::cout << thetaf << " ";
	std::cout << "axis_f " << axis_f << std::endl;

	assert(fabs(thetai - thetaf) < q.qThreshold);
	assert(axis_i == axis_f);
}

void qtrnTest::qtest5()
{
	HEADER("TEST 5: LERP")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q0 = qtrn::qFromAngleAxis(0.0f, axis);
	qtrn::qPrint("       q0", q0);
	qtrn q1 = qtrn::qFromAngleAxis(90.0f, axis);
	qtrn::qPrint("       q1", q1);
	qtrn qe = qtrn::qFromAngleAxis(30.0f, axis);
	qtrn::qPrint("       qe", qe);

	qtrn qLerp0 = qtrn::qLerp(q0, q1, 0.0f);
	qtrn::qPrint("  lerp(0)", qLerp0);
	assert(qtrn::qEqual(qLerp0, q0));

	qtrn qLerp1 = qtrn::qLerp(q0, q1, 1.0f);
	qtrn::qPrint("  lerp(1)", qLerp1);
	assert(qtrn::qEqual(qLerp1, q1));

	qtrn qlerp = qtrn::qLerp(q0, q1, 1 / 3.0f);
	qtrn::qPrint("lerp(1/3)", qlerp);
	qtrn::qPrintAngleAxis("lerp(1/3)", qlerp);

	assert(qtrn::qEqual(qlerp, qe) == 0);
}

void qtrnTest::qtest6()
{
	HEADER("TEST 6: SLERP")

		vec4 axis = { 0.0f, 1.0f, 0.0f, 1.0f };
	qtrn q0 = qtrn::qFromAngleAxis(0.0f, axis);
	qtrn::qPrint("        q0", q0);
	qtrn q1 = qtrn::qFromAngleAxis(90.0f, axis);
	qtrn::qPrint("        q1", q1);
	qtrn qe = qtrn::qFromAngleAxis(30.0f, axis);
	qtrn::qPrint("        qe", qe);

	qtrn qSlerp0 = qtrn::qSlerp(q0, q1, 0.0f);
	qtrn::qPrint("  slerp(0)", qSlerp0);
	assert(qtrn::qEqual(qSlerp0, q0));

	qtrn qSlerp1 = qtrn::qSlerp(q0, q1, 1.0f);
	qtrn::qPrint("  slerp(1)", qSlerp1);
	assert(qtrn::qEqual(qSlerp1, q1));

	qtrn qslerp = qtrn::qSlerp(q0, q1, 1 / 3.0f);
	qtrn::qPrint("slerp(1/3)", qslerp);
	qtrn::qPrintAngleAxis("slerp(1/3)", qslerp);

	assert(qtrn::qEqual(qslerp, qe));
}