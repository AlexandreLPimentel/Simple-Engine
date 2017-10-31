#include "vector.h"

/****************** vec2 ******************/

vec2::vec2(const vec2 & u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
}

vec2::vec2(float x, float y)
{
	data[0] = x;
	data[1] = y;
}

vec2::vec2(float c) {
	data[0] = c;
	data[1] = c;
}

vec2::vec2() {
	data[0] = 0;
	data[1] = 0;
}

vec2::~vec2()
{
}

void vec2::setX(float x) {
	data[0] = x;
}

void vec2::setY(float y) {
	data[1] = y;
}

float vec2::getX() {
	return data[0];
}

float vec2::getY() {
	return data[1];
}

const vec2 operator+(vec2 u, vec2 v)
{
	vec2 vec = u;
	vec += v;
	return vec;
}

const vec2 operator-(vec2 u, vec2 v)
{
	vec2 vec = u;
	vec -= v;
	return vec;
}

const vec2 operator*(vec2 u, float value) {
	return value * u;
}

const vec2 operator*(float value, vec2 u) {
	vec2 vec = u;
	vec *= value;
	return vec;
}

const vec2 operator/(vec2 u, float value) {
	vec2 vec = u;
	vec /= value;
	return vec;
}

const vec2 vec2::operator=(vec2 u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	return *this;
}

const vec2 & vec2::operator+=(const vec2 & v)
{
	data[0] += v.data[0];
	data[1] += v.data[1];
	return *this;
}

const vec2 & vec2::operator-=(const vec2 & v)
{
	data[0] -= v.data[0];
	data[1] -= v.data[1];
	return *this;
}
const vec2 & vec2::operator*=(float value)
{
	data[0] *= value;
	data[1] *= value;
	return *this;
}

const vec2 & vec2::operator/=(float value)
{
	data[0] /= value;
	data[1] /= value;
	return *this;
}

bool operator==(const vec2 & u, const vec2 & v)
{
	return u.data[0] == v.data[0] && u.data[1] == v.data[1];
}

bool operator!=(const vec2 & u, const vec2 & v)
{
	return !(u == v);
}

float vec2::quadrance() {
	return data[0] * data[0] + data[1] * data[1];
}

void vec2::normalize() {
	float nm = norm();
	data[0] /= nm;
	data[1] /= nm;
}

float vec2::norm() {
	return sqrt(quadrance());
}

float vec2::dot(vec2 v) {
	return data[0] * v.data[0] + data[1] * v.data[1];
}

ostream & operator<<(ostream & os, const vec2 & vector)
{
	os << '(' << vector.data[0] << ", " << vector.data[1] << ')' << '\0';
	return os;
}

istream & operator>>(istream & is, const vec2 & vector)
{
	//TODO
	return is;
}


/****************** vec3 ******************/

vec3::vec3(const vec4 & u, bool homogeneousCoordinates)
{
	if (homogeneousCoordinates) {
		float w = u.data[3];
		data[0] = u.data[0] / u.data[3];
		data[1] = u.data[1] / u.data[3];
		data[2] = u.data[2] / u.data[3];
	}
	else {
		data[0] = u.data[0];
		data[1] = u.data[1];
		data[2] = u.data[2];
		data[2] = 0.0f;
	}	
}

vec3::vec3(const vec4 & u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	data[2] = u.data[2];
}

vec3::vec3(const vec3 & u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	data[2] = u.data[2];
}

vec3::vec3(float x, float y, float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

vec3::vec3(float c) {
	data[0] = c;
	data[1] = c;
	data[2] = c;
}
vec3::vec3() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

vec3::~vec3()
{
}

void vec3::setX(float x) {
	data[0] = x;
}

void vec3::setY(float y) {
	data[1] = y;
}

void vec3::setZ(float z) {
	data[2] = z;
}

float vec3::getX() {
	return data[0];
}

float vec3::getY() {
	return data[1];
}

float vec3::getZ() {
	return data[2];
}

const vec3 operator+(vec3 u, vec3 v)
{
	vec3 vec = u;
	vec += v;
	return vec;
}

const vec3 operator-(vec3 u, vec3 v)
{
	vec3 vec = u;
	vec -= v;
	return vec;
}

const vec3 operator*(vec3 u, float value) {
	return value * u;
}

const vec3 operator*(float value, vec3 u) {
	vec3 vec = u;
	vec *= value;
	return vec;
}

const vec3 operator/(vec3 u, float value) {
	vec3 vec = u;
	vec /= value;
	return vec;
}

const vec3 vec3::operator=(vec3 u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	data[2] = u.data[2];
	return *this;
}

const vec3 & vec3::operator+=(const vec3 & v)
{
	data[0] += v.data[0];
	data[1] += v.data[1];
	data[2] += v.data[2];
	return *this;
}

const vec3 & vec3::operator-=(const vec3 & v)
{
	data[0] -= v.data[0];
	data[1] -= v.data[1];
	data[2] -= v.data[2];
	return *this;
}
const vec3 & vec3::operator*=(float value)
{
	data[0] *= value;
	data[1] *= value;
	data[2] *= value;
	return *this;
}

const vec3 & vec3::operator/=(float value)
{
	data[0] /= value;
	data[1] /= value;
	data[2] /= value;
	return *this;
}

bool operator==(const vec3 & u, const vec3 & v)
{
	return u.data[0] == v.data[0] && u.data[1] == v.data[1] && u.data[2] == v.data[2];
}

bool operator!=(const vec3 & u, const vec3 & v)
{
	return !(u == v);
}

float vec3::quadrance() {
	return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

void vec3::normalize() {
	float nm = norm();
	data[0] /= nm;
	data[1] /= nm;
	data[2] /= nm;
}

float vec3::norm() {
	return sqrt(quadrance());
}

float vec3::dot(vec3 v) {
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2];
}

vec3 vec3::cross(vec3 v) {
	return vec3(data[1] * v.data[2] - data[2] * v.data[1],
		data[2] * v.data[0] - data[0] * v.data[2],
		data[0] * v.data[1] - data[1] * v.data[0]);
}

vec3 vec3::rodrigues(vec3 axis, float angle)
{
	vec3 normalizedAxis = vec3(axis);
	normalizedAxis.normalize();
	float co = (float)cos((PI * angle) / 180);
	float si = (float)sin((PI * angle) / 180);
	return (co * (*this)) + (si * (normalizedAxis.cross(*this))) + (normalizedAxis * normalizedAxis.dot(*this) * (1 - co));
}

vec3 vec3::clean()
{
	this->data[0] *= (float)pow(10, 5);
	this->data[0] = round(this->data[0]);
	this->data[0] /= (float)pow(10, 5);
	this->data[1] *= (float)pow(10, 5);
	this->data[1] = round(this->data[1]);
	this->data[1] /= (float)pow(10, 5);
	this->data[2] *= (float)pow(10, 5);
	this->data[2] = round(this->data[2]);
	this->data[2] /= (float)pow(10, 5);
	return *this;
}

ostream & operator<<(ostream & os, const vec3 & vector)
{
	vec3 aux = vec3(vector);
	aux.clean();
	os << '(' << aux.data[0] << ", " << aux.data[1] << ", " << aux.data[2] << ')' << '\0';
	return os;
}

istream & operator>>(istream & is, const vec3 & vector)
{
	//TODO
	return is;
}





/****************** vec4 ******************/

vec4::vec4(const vec4 & u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	data[2] = u.data[2];
	data[3] = u.data[3];
}

vec4::vec4(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

vec4::vec4(vec3 vec, float w)
{
	data[0] = vec.getX();
	data[1] = vec.getY();
	data[2] = vec.getZ();
	data[3] = w;
}

vec4::vec4(vec3 vec)
{
	data[0] = vec.getX();
	data[1] = vec.getY();
	data[2] = vec.getZ();
	data[3] = 1;
}

vec4::vec4(float c) {
	data[0] = c;
	data[1] = c;
	data[2] = c;
	data[3] = c;
}
vec4::vec4() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
}

vec4::~vec4()
{
}

void vec4::setX(float x) {
	data[0] = x;
}

void vec4::setY(float y) {
	data[1] = y;
}

void vec4::setZ(float z) {
	data[2] = z;
}

void vec4::setW(float w) {
	data[3] = w;
}

float vec4::getX() {
	return data[0];
}

float vec4::getY() {
	return data[1];
}

float vec4::getZ() {
	return data[2];
}

float vec4::getW() {
	return data[3];
}


const vec4 operator+(vec4 u, vec4 v)
{
	vec4 vec = u;
	vec += v;
	return vec;
}

const vec4 operator-(vec4 u, vec4 v)
{
	vec4 vec = u;
	vec -= v;
	return vec;
}

const vec4 operator*(vec4 u, float value) {
	return value * u;
}

const vec4 operator*(float value, vec4 u) {
	vec4 vec = u;
	vec *= value;
	return vec;
}

const vec4 operator/(vec4 u, float value) {
	vec4 vec = u;
	vec /= value;
	return vec;
}

const vec4 vec4::operator=(vec4 u)
{
	data[0] = u.data[0];
	data[1] = u.data[1];
	data[2] = u.data[2];
	data[3] = u.data[3];
	return *this;
}

const vec4 & vec4::operator+=(const vec4 & v)
{
	this->data[0] += v.data[0];
	this->data[1] += v.data[1];
	this->data[2] += v.data[2];
	this->data[3] += v.data[3];
	return *this;
}

const vec4 & vec4::operator-=(const vec4 & v)
{
	this->data[0] -= v.data[0];
	this->data[1] -= v.data[1];
	this->data[2] -= v.data[2];
	this->data[3] -= v.data[3];
	return *this;
}
const vec4 & vec4::operator*=(float value)
{
	this->data[0] *= value;
	this->data[1] *= value;
	this->data[2] *= value;
	this->data[3] *= value;
	return *this;
}

const vec4 & vec4::operator/=(float value)
{
	this->data[0] /= value;
	this->data[1] /= value;
	this->data[2] /= value;
	this->data[3] /= value;
	return *this;
}

bool operator==(const vec4 & u, const vec4 & v)
{
	vec4 a = vec4(u);
	a.clean();
	vec4 b = vec4(v);
	b.clean();
	return a.data[0] == b.data[0] && a.data[1] == b.data[1] && a.data[2] == b.data[2] && a.data[3] == b.data[3];
}

bool operator!=(const vec4 & u, const vec4 & v)
{
	return !(u == v);
}

float vec4::quadrance() {
	return data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3];
}

void vec4::normalize() {
	float nm = 1 / norm();
	data[0] *= nm;
	data[1] *= nm;
	data[2] *= nm;
	data[3] *= nm;
}

vec4 vec4::normalize(vec4 v)
{
	vec4 vn;
	float s = 1 / (v.data[3] * sqrt(v.data[0]*v.data[0] + v.data[1]*v.data[1] + v.data[2]*v.data[2]));
	vn.data[0] = v.data[0] * s;
	vn.data[1] = v.data[1] * s;
	vn.data[2] = v.data[2] * s;
	vn.data[3] = 1.0f;
	return vn;

}

float vec4::norm() {
	return sqrt(quadrance());
}

float vec4::dot(vec4 v) {
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2] + data[3] * v.data[3];
}

ostream & operator<<(ostream & os, const vec4 & vector)
{
	os << '(' << vector.data[0] << ", " << vector.data[1] << ", " << vector.data[2] << ", " << vector.data[3] << ')' << '\0';
	return os;
}

istream & operator>>(istream & is, const vec4 & vector)
{
	//TODO
	return is;
}

vec4 vec4::clean()
{
	this->data[0] *= (float)pow(10, 3);
	this->data[0] = round(this->data[0]);
	this->data[0] /= (float)pow(10, 3);
	this->data[1] *= (float)pow(10, 3);
	this->data[1] = round(this->data[1]);
	this->data[1] /= (float)pow(10, 3);
	this->data[2] *= (float)pow(10, 3);
	this->data[2] = round(this->data[2]);
	this->data[2] /= (float)pow(10, 3);
	this->data[3] *= (float)pow(10, 3);
	this->data[3] = round(this->data[3]);
	this->data[3] /= (float)pow(10, 3);
	return *this;
}