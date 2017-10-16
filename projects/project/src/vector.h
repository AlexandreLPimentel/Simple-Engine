#pragma once
#include <iostream>  
#include <math.h>
#define PI 3.14159265
using namespace std;

struct vec2;
struct vec3;
struct vec4;

struct vec2
{
	friend vec3;
	friend vec4;
protected:
	float data[2];
public:
	//Vector creation and manipulation
	vec2(const vec2& u);
	vec2(float x, float y);
	vec2(float c);
	vec2(); //Defaults to 0,0
	~vec2();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();

	//non-destroying operators
	friend const vec2 operator+(vec2 u, vec2 v);
	friend const vec2 operator-(vec2 u, vec2 v);
	friend const vec2 operator*(vec2 u, float value);
	friend const vec2 operator*(float value, vec2 u);
	friend const vec2 operator/(vec2 u, float value);

	//lvalue destroying operators
	const vec2 operator=(vec2 u);
	const vec2& operator+=(const vec2& v);
	const vec2& operator-=(const vec2& v);
	const vec2& operator*=(float value);
	const vec2& operator/=(float value);

	//comparisons
	friend bool operator==(const vec2 &u, const vec2 & v);
	friend bool operator!=(const vec2 &u, const vec2 & v);

	//math
	float quadrance();
	void normalize();
	float norm();
	float dot(vec2 v);

	//print
	friend std::ostream& operator<<(std::ostream& os, const vec2& vector);
	friend std::istream& operator>>(std::istream& is, vec2& vector);
};

struct vec3
{
	friend vec2;
	friend vec4;
protected:
	float data[3];
public:
	//Vector creation and manipulation
	vec3(const vec4 & u, bool homogeneousCoordinates);
	vec3(const vec3 & u);
	vec3(float x, float y, float z);
	vec3(float c);
	vec3(); //Defaults to 0,0,0
	~vec3();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float getX();
	float getY();
	float getZ();

	//non-destroying operators
	friend const vec3 operator+(vec3 u, vec3 v);
	friend const vec3 operator-(vec3 u, vec3 v);
	friend const vec3 operator*(vec3 u, float value);
	friend const vec3 operator*(float value, vec3 u);
	friend const vec3 operator/(vec3 u, float value);

	//lvalue destroying operators
	const vec3 operator=(vec3 u);
	const vec3& operator+=(const vec3& v);
	const vec3& operator-=(const vec3& v);
	const vec3& operator*=(float value);
	const vec3& operator/=(float value);

	//comparisons
	friend bool operator==(const vec3 &u, const vec3 &v);
	friend bool operator!=(const vec3 &u, const vec3 &v);

	//math
	float quadrance();
	void normalize();
	float norm();
	float dot(vec3 v);
	vec3 cross(vec3 v);
	vec3 rodrigues(vec3 axis, float angle);
	vec3 clean();

	//print
	friend std::ostream& operator<<(std::ostream& os, const vec3& vector);
	friend std::istream& operator>>(std::istream& is, vec3& vector);
};

struct vec4
{
	friend vec2;
	friend vec3;
protected:
	float data[4];
public:
	//Vector creation and manipulation
	vec4(const vec4 & u);
	vec4(float x, float y, float z, float w);
	vec4(vec3 vec, float w);
	vec4(vec3 vec);
	vec4(float c);
	vec4(); //Defaults to 0,0,0,0
	~vec4();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);
	float getX();
	float getY();
	float getZ();
	float getW();

	//non-destroying operators
	friend const vec4 operator+(vec4 u, vec4 v);
	friend const vec4 operator-(vec4 u, vec4 v);
	friend const vec4 operator*(vec4 u, float value);
	friend const vec4 operator*(float value, vec4 u);
	friend const vec4 operator/(vec4 u, float value);

	//lvalue destroying operators
	const vec4 operator=(vec4 u);
	const vec4& operator+=(const vec4& v);
	const vec4& operator-=(const vec4& v);
	const vec4& operator*=(float value);
	const vec4& operator/=(float value);

	//comparisons
	friend bool operator==(const vec4 &u, const vec4 & v);
	friend bool operator!=(const vec4 &u, const vec4 & v);

	//math
	float quadrance();
	void normalize();
	float norm();
	float dot(vec4 v);
	vec4 clean();

	//print
	friend std::ostream& operator<<(std::ostream& os, const vec4& vector);
	friend std::istream& operator>>(std::istream& is, vec4& vector);
};