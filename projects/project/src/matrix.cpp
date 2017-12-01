#include "matrix.h"

/********************mat2*******************/


mat2::mat2(const mat2 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
}

mat2::mat2(const mat3 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[3];
	data[3] = m.data[4];
}

mat2::mat2(const mat4 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[4];
	data[3] = m.data[5];
}

mat2::mat2(float a, float b, float c, float d)
{
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
}

mat2::~mat2()
{
}

void mat2::setCoordinate(int line, int column, float value)
{
	if (line > 1 || column > 1) {
		throw std::invalid_argument("mat2 only has 2 rows and columns.");
	}
	data[2 * line + column] = value;
}

float mat2::getCoordinate(int line, int column)
{
	if (line > 1 || column > 1) {
		throw std::invalid_argument("mat2 only has 2 rows and columns.");
	}
	return data[2 * line + column];
}

mat2 mat2::identityMatrix()
{
	return mat2(
		1, 0,
		0, 1);
}

mat2 mat2::scaleMatrix(vec2 vec)
{
	float x = vec.getX();
	float y = vec.getY();
	return mat2(
		x, 0,
		0, y);
}

mat2 mat2::scaleMatrix(float s)
{

	return mat2(
		s, 0,
		0, s);

}

mat2 mat2::rotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat2(
		co, -si,
		si, co);
}


const mat2 mat2::operator=(mat2 m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	return *this;
}

const mat2 & mat2::operator+=(const mat2 & m)
{
	data[0] += m.data[0];
	data[1] += m.data[1];
	data[2] += m.data[2];
	data[3] += m.data[3];
	return *this;
}

const mat2 & mat2::operator-=(const mat2 & m)
{
	data[0] -= m.data[0];
	data[1] -= m.data[1];
	data[2] -= m.data[2];
	data[3] -= m.data[3];
	return *this;
}

const mat2 & mat2::operator*=(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	data[3] *= value;
	return *this;
}

const mat2 & mat2::operator*=(mat2 m)
{
	vec2 line1 = vec2(data[0], data[1]);
	vec2 line2 = vec2(data[2], data[3]);
	vec2 col1 = vec2(m.data[0], m.data[2]);
	vec2 col2 = vec2(m.data[1], m.data[3]);
	data[0] = line1.dot(col1);
	data[1] = line1.dot(col2);
	data[2] = line2.dot(col1);
	data[3] = line2.dot(col2);
	return *this;
}

mat2 mat2::transpose(mat2 m)
{
	return mat2(
		m.data[0], m.data[2],
		m.data[1], m.data[3]);
}

void mat2::transpose()
{
	float a = data[0];
	float b = data[1];
	float c = data[2];
	float d = data[3];

	data[0] = a;
	data[2] = b;
	data[1] = c;
	data[3] = d;
}

float mat2::determinant()
{
	return
		data[0] * data[3] - data[1] * data[2];
}

mat2 mat2::inverse(mat2 m)
{
	mat2 inv = mat2(m);
	inv.inverse();
	return inv;
}

void mat2::inverse()
{
	float inverse[16];
	float det = determinant();

	if (det == 0) {
		throw std::invalid_argument("The given matrix can't be inversed.");
	}

	float multiplier = 1 / det;

	inverse[0] = multiplier * data[3];
	inverse[1] = multiplier * (-data[1]);
	inverse[2] = multiplier * (-data[2]);
	inverse[3] = multiplier * data[0];


	for (int i = 0; i < 4; i++) {
		data[i] = inverse[i];
	}
}

float * mat2::getColumnMajor() const
{
	mat2 n = transpose(*this);
	return n.getRowMajor();
}

float * mat2::getRowMajor() const
{
	float* vec = (float*)malloc(4 * sizeof(float));
	memcpy(vec, data, 4 * sizeof(float));
	return vec;
}

bool operator==(const mat2 & m, const mat2 & n)
{
	return m.data[0] == n.data[0]
		&& m.data[1] == n.data[1]
		&& m.data[2] == n.data[2]
		&& m.data[3] == n.data[3];
}

bool operator!=(const mat2 & m, const mat2 & n) {
	return !(m == n);
}

std::ostream & operator<<(std::ostream & os, const mat2 & matrix)
{
	os << '(' << matrix.data[0] << ' ' << matrix.data[1] << '\n'
		<< ' ' << matrix.data[2] << ' ' << matrix.data[3] << ')' << '\0';
	return os;
}

std::istream & operator>>(std::istream & is, mat2 & matrix)
{
	//TODO
	return is;
}

const mat2 operator+(mat2 m, mat2 n)
{
	mat2 o = mat2(m);
	return o += n;
}

const mat2 operator-(mat2 m, mat2 n)
{
	mat2 o = mat2(m);
	return o -= n;
}

const mat2 operator*(mat2 m, float value)
{
	mat2 o = mat2(m);
	return o *= value;
}

const mat2 operator*(float value, mat2 m)
{
	mat2 o = mat2(m);
	return o *= value;
}

const vec2 operator*(mat2 m, vec2 v)
{
	float x = v.getX();
	float y = v.getY();
	vec2 u = vec2(
		m.data[0] * x + m.data[1] * y,
		m.data[2] * x + m.data[3] * y
	);
	return u;
}

const mat2 operator*(mat2 m, mat2 n)
{

	mat2 o = mat2(m);
	return o *= n;
}

mat2 mat2::clean() {
	for (int i = 0; i < 4; i++) {
		this->data[i] *= (float)pow(10, 3);
		this->data[i] = (int) this->data[i];
		this->data[i] /= (float)pow(10, 3);
	}
	return *this;
}

/********************mat3*******************/


mat3::mat3(const mat2 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = 0;
	data[3] = m.data[2];
	data[4] = m.data[3];
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
}

mat3::mat3(const mat3 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
}

mat3::mat3(const mat4 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[4];
	data[4] = m.data[5];
	data[5] = m.data[6];
	data[6] = m.data[8];
	data[7] = m.data[9];
	data[8] = m.data[10];
}

mat3::mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	data[4] = e;
	data[5] = f;
	data[6] = g;
	data[7] = h;
	data[8] = i;
}

mat3::~mat3()
{
}

void mat3::setCoordinate(int line, int column, float value)
{
	if (line > 3 || column > 3) {
		throw std::invalid_argument("mat3 only has 3 rows and columns.");
	}
	data[3 * line + column] = value;
}

float mat3::getCoordinate(int line, int column)
{
	if (line > 3 || column > 3) {
		throw std::invalid_argument("mat3 only has 3 rows and columns.");
	}
	return data[3 * line + column];
}

mat3 mat3::identityMatrix()
{
	return mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
}

mat3 mat3::scaleMatrix(vec3 vec)
{
	float x = vec.getX();
	float y = vec.getY();
	float z = vec.getZ();
	return mat3(
		x, 0, 0,
		0, y, 0,
		0, 0, z);
}

mat3 mat3::scaleMatrix(float s)
{

	return mat3(
		s, 0, 0,
		0, s, 0,
		0, 0, s);

}

mat3 mat3::translationMatrix(vec2 vec)
{
	float x = vec.getX();
	float y = vec.getY();
	return mat3(
		1, 0, x,
		0, 1, y,
		0, 0, 1);
}

mat3 mat3::xRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat3(
		1, 0, 0,
		0, co, -si,
		0, si, co);
}

mat3 mat3::yRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat3(
		co, 0, si,
		0, 1, 0,
		-si, 0, co);
}

mat3 mat3::zRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat3(
		co, -si, 0,
		si, co, 0,
		0, 0, 1);
}

const mat3 mat3::operator=(mat3 m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	return *this;
}

const mat3 & mat3::operator+=(const mat3 & m)
{
	data[0] += m.data[0];
	data[1] += m.data[1];
	data[2] += m.data[2];
	data[3] += m.data[3];
	data[4] += m.data[4];
	data[5] += m.data[5];
	data[6] += m.data[6];
	data[7] += m.data[7];
	data[8] += m.data[8];
	return *this;
}

const mat3 & mat3::operator-=(const mat3 & m)
{
	data[0] -= m.data[0];
	data[1] -= m.data[1];
	data[2] -= m.data[2];
	data[3] -= m.data[3];
	data[4] -= m.data[4];
	data[5] -= m.data[5];
	data[6] -= m.data[6];
	data[7] -= m.data[7];
	data[8] -= m.data[8];
	return *this;
}

const mat3 & mat3::operator*=(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	data[3] *= value;
	data[4] *= value;
	data[5] *= value;
	data[6] *= value;
	data[7] *= value;
	data[8] *= value;
	return *this;
}

const mat3 & mat3::operator*=(mat3 m)
{
	vec3 line1 = vec3(data[0], data[1], data[2]);
	vec3 line2 = vec3(data[3], data[4], data[5]);
	vec3 line3 = vec3(data[6], data[7], data[8]);
	vec3 col1 = vec3(m.data[0], m.data[3], m.data[6]);
	vec3 col2 = vec3(m.data[1], m.data[4], m.data[7]);
	vec3 col3 = vec3(m.data[2], m.data[5], m.data[8]);
	data[0] = line1.dot(col1);
	data[1] = line1.dot(col2);
	data[2] = line1.dot(col3);
	data[3] = line2.dot(col1);
	data[4] = line2.dot(col2);
	data[5] = line2.dot(col3);
	data[6] = line3.dot(col1);
	data[7] = line3.dot(col2);
	data[8] = line3.dot(col3);
	return *this;
}

mat3 mat3::transpose(mat3 m)
{
	return mat3(
		m.data[0], m.data[3], m.data[6],
		m.data[1], m.data[4], m.data[7],
		m.data[2], m.data[5], m.data[8]);
}

void mat3::transpose()
{
	float a = data[0];
	float b = data[1];
	float c = data[2];
	float d = data[3];
	float e = data[4];
	float f = data[5];
	float g = data[6];
	float h = data[7];
	float i = data[8];

	data[0] = a;
	data[3] = b;
	data[6] = c;
	data[1] = d;
	data[4] = e;
	data[7] = f;
	data[2] = g;
	data[5] = h;
	data[8] = i;
}

float mat3::determinant()
{
	return
		data[0] * (data[4] * data[8] - data[5] * data[7])
		- data[1] * (data[3] * data[8] - data[5] * data[6])
		+ data[2] * (data[3] * data[7] - data[4] * data[6]);
}

mat3 mat3::inverse(mat3 m)
{
	mat3 inv = mat3(m);
	inv.inverse();
	return inv;
}

void mat3::inverse()
{
	float inverse[16];
	float det = determinant();

	if (det == 0) {
		throw std::invalid_argument("The given matrix can't be inversed.");
	}

	float multiplier = 1 / det;

	inverse[0] = multiplier * (data[4] * data[8] - data[5] * data[7]);
	inverse[1] = multiplier * (data[2] * data[7] - data[1] * data[8]);
	inverse[2] = multiplier * (data[1] * data[5] - data[2] * data[4]);
	inverse[3] = multiplier * (data[5] * data[6] - data[3] * data[8]);
	inverse[4] = multiplier * (data[0] * data[8] - data[2] * data[6]);
	inverse[5] = multiplier * (data[2] * data[3] - data[0] * data[5]);
	inverse[6] = multiplier * (data[3] * data[7] - data[4] * data[6]);
	inverse[7] = multiplier * (data[1] * data[6] - data[0] * data[7]);
	inverse[8] = multiplier * (data[0] * data[4] - data[1] * data[3]);


	for (int i = 0; i < 9; i++) {
		data[i] = inverse[i];
	}
}

float * mat3::getColumnMajor() const
{
	mat3 n = transpose(*this);
	return n.getRowMajor();
}

float * mat3::getRowMajor() const
{
	float* vec = (float*)malloc(9 * sizeof(float));
	memcpy(vec, data, 9 * sizeof(float));
	return vec;
}

bool operator==(const mat3 & m, const mat3 & n)
{
	return m.data[0] == n.data[0]
		&& m.data[1] == n.data[1]
		&& m.data[2] == n.data[2]
		&& m.data[3] == n.data[3]
		&& m.data[4] == n.data[4]
		&& m.data[5] == n.data[5]
		&& m.data[6] == n.data[6]
		&& m.data[7] == n.data[7]
		&& m.data[8] == n.data[8];
}

bool operator!=(const mat3 & m, const mat3 & n) {
	return !(m == n);
}

std::ostream & operator<<(std::ostream & os, const mat3 & matrix)
{
	os << '(' << matrix.data[0] << ' ' << matrix.data[1] << ' ' << matrix.data[2] << '\n'
		<< ' ' << matrix.data[3] << ' ' << matrix.data[4] << ' ' << matrix.data[5] << '\n'
		<< ' ' << matrix.data[6] << ' ' << matrix.data[7] << ' ' << matrix.data[8] << ')' << '\0';
	return os;
}

std::istream & operator>>(std::istream & is, mat3 & matrix)
{
	//TODO
	return is;
}

const mat3 operator+(mat3 m, mat3 n)
{
	mat3 o = mat3(m);
	return o += n;
}

const mat3 operator-(mat3 m, mat3 n)
{
	mat3 o = mat3(m);
	return o -= n;
}

const mat3 operator*(mat3 m, float value)
{
	mat3 o = mat3(m);
	return o *= value;
}

const mat3 operator*(float value, mat3 m)
{
	mat3 o = mat3(m);
	return o *= value;
}

const vec3 operator*(mat3 m, vec3 v)
{
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();
	vec3 u = vec3(
		m.data[0] * x + m.data[1] * y + m.data[2] * z,
		m.data[3] * x + m.data[4] * y + m.data[5] * z,
		m.data[6] * x + m.data[7] * y + m.data[8] * z
	);
	return u;
}

const mat3 operator*(mat3 m, mat3 n)
{

	mat3 o = mat3(m);
	return o *= n;
}

mat3 mat3::clean() {
	for (int i = 0; i < 9; i++) {
		this->data[i] *= (float)pow(10, 3);
		this->data[i] = round(this->data[i]);
		this->data[i] /= (float)pow(10, 3);
	}
	return *this;
}




/**********************mat4***************************/

mat4::mat4()
{
}

mat4::mat4(const mat2 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = 0;
	data[3] = 0;
	data[4] = m.data[2];
	data[5] = m.data[3];
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
}

mat4::mat4(const mat3 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = 0;
	data[4] = m.data[3];
	data[5] = m.data[4];
	data[6] = m.data[5];
	data[7] = 0;
	data[8] = m.data[6];
	data[9] = m.data[7];
	data[10] = m.data[8];
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
}

mat4::mat4(const mat4 & m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	data[9] = m.data[9];
	data[10] = m.data[10];
	data[11] = m.data[11];
	data[12] = m.data[12];
	data[13] = m.data[13];
	data[14] = m.data[14];
	data[15] = m.data[15];
}

mat4::mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
	data[4] = e;
	data[5] = f;
	data[6] = g;
	data[7] = h;
	data[8] = i;
	data[9] = j;
	data[10] = k;
	data[11] = l;
	data[12] = m;
	data[13] = n;
	data[14] = o;
	data[15] = p;
}

mat4::~mat4()
{
}

void mat4::setCoordinate(int line, int column, float value)
{
	if (line > 4 || column > 4) {
		throw std::invalid_argument("mat4 only has 4 rows and columns.");
	}
	data[4 * line + column] = value;
}

float mat4::getCoordinate(int line, int column)
{
	if (line > 4 || column > 4) {
		throw std::invalid_argument("mat4 only has 4 rows and columns.");
	}
	return data[4 * line + column];
}

mat4 mat4::identityMatrix()
{
	return mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

mat4 mat4::scaleMatrix(vec3 vec)
{
	float x = vec.getX();
	float y = vec.getY();
	float z = vec.getZ();
	return mat4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

mat4 mat4::scaleMatrix(float s)
{

	return mat4(
		s, 0, 0, 0,
		0, s, 0, 0,
		0, 0, s, 0,
		0, 0, 0, 1);

}

mat4 mat4::translationMatrix(vec3 vec)
{
	float x = vec.getX();
	float y = vec.getY();
	float z = vec.getZ();
	return mat4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
}

mat4 mat4::xRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat4(
		1, 0, 0, 0,
		0, co, -si, 0,
		0, si, co, 0,
		0, 0, 0, 1);
}

mat4 mat4::yRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat4(
		co, 0, si, 0,
		0, 1, 0, 0,
		-si, 0, co, 0,
		0, 0, 0, 1);
}

mat4 mat4::zRotationMatrix(float angle)
{
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return mat4(
		co, -si, 0, 0,
		si, co, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

mat4 mat4::lookAt(vec3 eye, vec3 center, vec3 up)
{
	vec3 v = center - eye;
	v.normalize();

	vec3 s = v.cross(up);
	s.normalize();

	vec3 u = s.cross(v);

	return mat4(
		s.getX(), s.getY(), s.getZ(), -s.dot(eye),
		u.getX(), u.getY(), u.getZ(), -u.dot(eye),
		-v.getX(), -v.getY(), -v.getZ(), v.dot(eye),
		0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 mat4::ortho(float left, float right, float top, float bottom, float near, float far)
{
	return	mat4(
		2 / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
		0.0f, 2 / (top - bottom), 0.0f, (bottom + top) / (bottom - top),
		0.0f, 0.0f, 2 / (near - far), (near + far) / (near - far),
		0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 mat4::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float d = 1 / tan(((PI * fovy) / 180) / 2);
	return mat4(
		d / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, d, 0.0f, 0.0f,
		0.0f, 0.0f, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zNear - zFar),
		0.0f, 0.0f, -1.0f, 0);
}

const mat4 mat4::operator=(mat4 m)
{
	data[0] = m.data[0];
	data[1] = m.data[1];
	data[2] = m.data[2];
	data[3] = m.data[3];
	data[4] = m.data[4];
	data[5] = m.data[5];
	data[6] = m.data[6];
	data[7] = m.data[7];
	data[8] = m.data[8];
	data[9] = m.data[9];
	data[10] = m.data[10];
	data[11] = m.data[11];
	data[12] = m.data[12];
	data[13] = m.data[13];
	data[14] = m.data[14];
	data[15] = m.data[15];
	return *this;
}

const mat4 & mat4::operator+=(const mat4 & m)
{
	data[0] += m.data[0];
	data[1] += m.data[1];
	data[2] += m.data[2];
	data[3] += m.data[3];
	data[4] += m.data[4];
	data[5] += m.data[5];
	data[6] += m.data[6];
	data[7] += m.data[7];
	data[8] += m.data[8];
	data[9] += m.data[9];
	data[10] += m.data[10];
	data[11] += m.data[11];
	data[12] += m.data[12];
	data[13] += m.data[13];
	data[14] += m.data[14];
	data[15] += m.data[15];
	return *this;
}

const mat4 & mat4::operator-=(const mat4 & m)
{
	data[0] -= m.data[0];
	data[1] -= m.data[1];
	data[2] -= m.data[2];
	data[3] -= m.data[3];
	data[4] -= m.data[4];
	data[5] -= m.data[5];
	data[6] -= m.data[6];
	data[7] -= m.data[7];
	data[8] -= m.data[8];
	data[9] -= m.data[9];
	data[10] -= m.data[10];
	data[11] -= m.data[11];
	data[12] -= m.data[12];
	data[13] -= m.data[13];
	data[14] -= m.data[14];
	data[15] -= m.data[15];
	return *this;
}

const mat4 & mat4::operator*=(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	data[3] *= value;
	data[4] *= value;
	data[5] *= value;
	data[6] *= value;
	data[7] *= value;
	data[8] *= value;
	data[9] *= value;
	data[10] *= value;
	data[11] *= value;
	data[12] *= value;
	data[13] *= value;
	data[14] *= value;
	data[15] *= value;
	return *this;
}

const mat4 & mat4::operator*=(mat4 m)
{
	vec4 line1 = vec4(data[0], data[1], data[2], data[3]);
	vec4 line2 = vec4(data[4], data[5], data[6], data[7]);
	vec4 line3 = vec4(data[8], data[9], data[10], data[11]);
	vec4 line4 = vec4(data[12], data[13], data[14], data[15]);
	vec4 col1 = vec4(m.data[0], m.data[4], m.data[8], m.data[12]);
	vec4 col2 = vec4(m.data[1], m.data[5], m.data[9], m.data[13]);
	vec4 col3 = vec4(m.data[2], m.data[6], m.data[10], m.data[14]);
	vec4 col4 = vec4(m.data[3], m.data[7], m.data[11], m.data[15]);

	data[0] = line1.dot(col1);
	data[1] = line1.dot(col2);
	data[2] = line1.dot(col3);
	data[3] = line1.dot(col4);
	data[4] = line2.dot(col1);
	data[5] = line2.dot(col2);
	data[6] = line2.dot(col3);
	data[7] = line2.dot(col4);
	data[8] = line3.dot(col1);
	data[9] = line3.dot(col2);
	data[10] = line3.dot(col3);
	data[11] = line3.dot(col4);
	data[12] = line4.dot(col1);
	data[13] = line4.dot(col2);
	data[14] = line4.dot(col3);
	data[15] = line4.dot(col4);
	return *this;
}

mat4 mat4::transpose(mat4 m)
{
	return mat4(m.data[0], m.data[4], m.data[8], m.data[12],
		m.data[1], m.data[5], m.data[9], m.data[13],
		m.data[2], m.data[6], m.data[10], m.data[14],
		m.data[3], m.data[7], m.data[11], m.data[15]);
}

void mat4::transpose()
{
	float a = data[0];
	float b = data[1];
	float c = data[2];
	float d = data[3];
	float e = data[4];
	float f = data[5];
	float g = data[6];
	float h = data[7];
	float i = data[8];
	float j = data[9];
	float k = data[10];
	float l = data[11];
	float m = data[12];
	float n = data[13];
	float o = data[14];
	float p = data[15];

	data[0] = a;
	data[4] = b;
	data[8] = c;
	data[12] = d;
	data[1] = e;
	data[5] = f;
	data[9] = g;
	data[13] = h;
	data[2] = i;
	data[6] = j;
	data[10] = k;
	data[14] = l;
	data[3] = m;
	data[7] = n;
	data[11] = o;
	data[15] = p;
}

float mat4::determinant()
{
	return
		data[12] * data[9] * data[6] * data[3] -
		data[8] * data[13] * data[6] * data[3] -
		data[12] * data[5] * data[10] * data[3] +
		data[4] * data[13] * data[10] * data[3] +
		data[8] * data[5] * data[14] * data[3] -
		data[4] * data[9] * data[14] * data[3] -
		data[12] * data[9] * data[2] * data[7] +
		data[8] * data[13] * data[2] * data[7] +
		data[12] * data[1] * data[10] * data[7] -
		data[0] * data[13] * data[10] * data[7] -
		data[8] * data[1] * data[14] * data[7] +
		data[0] * data[9] * data[14] * data[7] +
		data[12] * data[5] * data[2] * data[11] -
		data[4] * data[13] * data[2] * data[11] -
		data[12] * data[1] * data[6] * data[11] +
		data[0] * data[13] * data[6] * data[11] +
		data[4] * data[1] * data[14] * data[11] -
		data[0] * data[5] * data[14] * data[11] -
		data[8] * data[5] * data[2] * data[15] +
		data[4] * data[9] * data[2] * data[15] +
		data[8] * data[1] * data[6] * data[15] -
		data[0] * data[9] * data[6] * data[15] -
		data[4] * data[1] * data[10] * data[15] +
		data[0] * data[5] * data[10] * data[15];
}

mat4 mat4::inverse(mat4 m)
{
	mat4 inv = mat4(m);
	inv.inverse();
	return inv;
}

void mat4::inverse()
{
	float inverse[16];

	inverse[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	inverse[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	inverse[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	inverse[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	inverse[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	inverse[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	inverse[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	inverse[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	inverse[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	inverse[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	inverse[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	inverse[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	inverse[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	inverse[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	inverse[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	inverse[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];


	float determinant = data[0] * inverse[0] + data[1] * inverse[4] + data[2] * inverse[8] + data[3] * inverse[12];

	if (determinant == 0) {
		throw std::invalid_argument("The given matrix can't be inversed.");
	}

	determinant = 1.0f / determinant;

	for (int i = 0; i < 16; i++) {
		data[i] = inverse[i] * determinant;
	}
}

float * mat4::getColumnMajor() const
{
	mat4 n = transpose(*this);
	return n.getRowMajor();
}

float * mat4::getRowMajor() const
{
	float* vec = (float*)malloc(16 * sizeof(float));
	memcpy(vec, data, 16 * sizeof(float));
	return vec;
}

bool operator==(const mat4 & m, const mat4 & n)
{
	return m.data[0] == n.data[0]
		&& m.data[1] == n.data[1]
		&& m.data[2] == n.data[2]
		&& m.data[3] == n.data[3]
		&& m.data[4] == n.data[4]
		&& m.data[5] == n.data[5]
		&& m.data[6] == n.data[6]
		&& m.data[7] == n.data[7]
		&& m.data[8] == n.data[8]
		&& m.data[9] == n.data[9]
		&& m.data[10] == n.data[10]
		&& m.data[11] == n.data[11]
		&& m.data[12] == n.data[12]
		&& m.data[13] == n.data[13]
		&& m.data[14] == n.data[14]
		&& m.data[15] == n.data[15];
}

bool operator!=(const mat4 & m, const mat4 & n) {
	return !(m == n);
}

std::ostream & operator<<(std::ostream & os, const mat4 & matrix)
{
	os << '(' << matrix.data[0] << ' ' << matrix.data[1] << ' ' << matrix.data[2] << ' ' << matrix.data[3] << '\n'
		<< ' ' << matrix.data[4] << ' ' << matrix.data[5] << ' ' << matrix.data[6] << ' ' << matrix.data[7] << '\n'
		<< ' ' << matrix.data[8] << ' ' << matrix.data[9] << ' ' << matrix.data[10] << ' ' << matrix.data[11] << '\n'
		<< ' ' << matrix.data[12] << ' ' << matrix.data[13] << ' ' << matrix.data[14] << ' ' << matrix.data[15] << ')' << '\0';
	return os;
}

std::istream & operator>>(std::istream & is, mat4 & matrix)
{
	//TODO
	return is;
}

const mat4 operator+(mat4 m, mat4 n)
{
	mat4 o = mat4(m);
	return o += n;
}

const mat4 operator-(mat4 m, mat4 n)
{
	mat4 o = mat4(m);
	return o -= n;
}

const mat4 operator*(mat4 m, float value)
{
	mat4 o = mat4(m);
	return o *= value;
}

const mat4 operator*(float value, mat4 m)
{
	mat4 o = mat4(m);
	return o *= value;
}

const vec4 operator*(mat4 m, vec4 v)
{
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();
	float w = v.getW();
	vec4 u = vec4(
		m.data[0] * x + m.data[1] * y + m.data[2] * z + m.data[3] * w,
		m.data[4] * x + m.data[5] * y + m.data[6] * z + m.data[7] * w,
		m.data[8] * x + m.data[9] * y + m.data[10] * z + m.data[11] * w,
		m.data[12] * x + m.data[13] * y + m.data[14] * z + m.data[15] * w
	);
	return u;
}

const mat4 operator*(mat4 m, mat4 n)
{

	mat4 o = mat4(m);
	return o *= n;
}

mat4 mat4::clean() {
	for (int i = 0; i < 16; i++) {
		this->data[i] *= (float)pow(10, 3);
		this->data[i] = (int) this->data[i];
		this->data[i] /= (float)pow(10, 3);
	}
	return *this;
}