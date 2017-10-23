#pragma once
#include <iostream>  
#include <math.h>
#include "vector.h"
#define PI 3.14159265
using namespace std;

struct mat2;
struct mat3;
struct mat4;


struct mat2
{
	friend mat3;
	friend mat4;
protected:
	float data[16];
public:
	//Matrix creation and manipulation
	mat2(const mat2 & m);
	mat2(const mat3 & m);
	mat2(const mat4 & m);
	mat2(float a, float b,
		float c, float d);
	~mat2();
	void setCoordinate(int line, int column, float value);
	float getCoordinate(int line, int column);

	//non-destroying operators
	friend const mat2 operator+(mat2 m, mat2 n);
	friend const mat2 operator-(mat2 m, mat2 n);
	friend const mat2 operator*(mat2 m, float value);
	friend const mat2 operator*(float value, mat2 m);
	friend const vec2 operator*(mat2 m, vec2 v);
	friend const mat2 operator*(mat2 m, mat2 n);

	//special matrices
	static mat2 identityMatrix();
	static mat2 scaleMatrix(vec2 vec);
	static mat2 scaleMatrix(float scale);
	static mat2 rotationMatrix(float angle);

	//lvalue destroying operators
	const mat2 operator=(mat2 m);
	const mat2& operator+=(const mat2& m);
	const mat2& operator-=(const mat2& m);
	const mat2& operator*=(float value);
	const mat2& operator*=(mat2 m);

	//comparisons
	friend bool operator==(const mat2 &m, const mat2 &n);
	friend bool operator!=(const mat2 &m, const mat2 &n);

	//math
	static mat2 transpose(mat2 m);
	void transpose();
	float determinant();
	static mat2 inverse(mat2 m);
	void inverse();
	const float* getColumnMajor();
	const float* getRowMajor();

	//print
	friend std::ostream& operator<<(std::ostream& os, const mat2& matrix);
	friend std::istream& operator>>(std::istream& is, mat2& matrix);

	mat2 clean();
};



struct mat3
{
	friend mat2;
	friend mat4;
protected:
	float data[16];
public:
	//Matrix creation and manipulation
	mat3(const mat2 & m);
	mat3(const mat3 & m);
	mat3(const mat4 & m);
	mat3(float a, float b, float c,
		float d, float e, float f,
		float g, float h, float i);
	~mat3();
	void setCoordinate(int line, int column, float value);
	float getCoordinate(int line, int column);

	//non-destroying operators
	friend const mat3 operator+(mat3 m, mat3 n);
	friend const mat3 operator-(mat3 m, mat3 n);
	friend const mat3 operator*(mat3 m, float value);
	friend const mat3 operator*(float value, mat3 m);
	friend const vec3 operator*(mat3 m, vec3 v);
	friend const mat3 operator*(mat3 m, mat3 n);

	//special matrices
	static mat3 identityMatrix();
	static mat3 scaleMatrix(vec3 vec);
	static mat3 scaleMatrix(float scale);
	static mat3 translationMatrix(vec2 vec);
	static mat3 xRotationMatrix(float angle);
	static mat3 yRotationMatrix(float angle);
	static mat3 zRotationMatrix(float angle);

	//lvalue destroying operators
	const mat3 operator=(mat3 m);
	const mat3& operator+=(const mat3& m);
	const mat3& operator-=(const mat3& m);
	const mat3& operator*=(float value);
	const mat3& operator*=(mat3 m);

	//comparisons
	friend bool operator==(const mat3 &m, const mat3 &n);
	friend bool operator!=(const mat3 &m, const mat3 &n);

	//math
	static mat3 transpose(mat3 m);
	void transpose();
	float determinant();
	static mat3 inverse(mat3 m);
	void inverse();
	const float* getColumnMajor();
	const float* getRowMajor();

	//print
	friend std::ostream& operator<<(std::ostream& os, const mat3& matrix);
	friend std::istream& operator>>(std::istream& is, mat3& matrix);

	mat3 clean();
};



struct mat4
{
	friend mat2;
	friend mat3;
protected:
	float data[16];
public:
	//Matrix creation and manipulation
	mat4(const mat2 & m);
	mat4(const mat3 & m);
	mat4(const mat4 & m);
	mat4(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);
	~mat4();
	void setCoordinate(int line, int column, float value);
	float getCoordinate(int line, int column);

	//non-destroying operators
	friend const mat4 operator+(mat4 m, mat4 n);
	friend const mat4 operator-(mat4 m, mat4 n);
	friend const mat4 operator*(mat4 m, float value);
	friend const mat4 operator*(float value, mat4 m);
	friend const vec4 operator*(mat4 m, vec4 v);
	friend const mat4 operator*(mat4 m, mat4 n);

	//special matrices
	static mat4 identityMatrix();
	static mat4 scaleMatrix(vec3 vec);
	static mat4 scaleMatrix(float scale);
	static mat4 translationMatrix(vec3 vec);
	static mat4 xRotationMatrix(float angle);
	static mat4 yRotationMatrix(float angle);
	static mat4 zRotationMatrix(float angle);
	static mat4 lookAt(vec3 eye, vec3 center, vec3 up);
	static mat4 ortho(float left, float right, float top, float bottom, float near, float far);
	static mat4 perspective(float fovy, float aspect, float zNear, float zFar);

	//lvalue destroying operators
	const mat4 operator=(mat4 m);
	const mat4& operator+=(const mat4& m);
	const mat4& operator-=(const mat4& m);
	const mat4& operator*=(float value);
	const mat4& operator*=(mat4 m);

	//comparisons
	friend bool operator==(const mat4 &m, const mat4 &n);
	friend bool operator!=(const mat4 &m, const mat4 &n);

	//math
	static mat4 transpose(mat4 m);
	void transpose();
	float determinant();
	static mat4 inverse(mat4 m);
	void inverse();
	const float* getColumnMajor();
	const float* getRowMajor();

	//print
	friend std::ostream& operator<<(std::ostream& os, const mat4& matrix);
	friend std::istream& operator>>(std::istream& is, mat4& matrix);

	mat4 clean();
};




