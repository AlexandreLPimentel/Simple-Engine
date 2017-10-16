#pragma once
#include "vector.h"
#include "matrix.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

#define SIZE_RATIO 0.25

typedef struct
{
	vec4 XYZW;
	vec4 RGBA;
} Vertex;

class GameObject
{
public:
	Vertex* vertices;
	GLuint numVertices;
	GLubyte* indices;
	GLuint numIndices;
	mat4 transformation = mat4::identityMatrix();
	GLuint VaoId, VboId[2];

	GameObject();
	~GameObject();
	void draw(GLint UniformId);
	void rotate(mat4 rotation);
	void scale(mat4 scale);
	void translate(mat4 translation);
	GLsizeiptr wholeVertexBufferSize() const;
	GLsizeiptr vertexBufferSize() const;
	GLsizeiptr colorBufferSize() const;
	GLsizeiptr indexBufferSize() const;

	static GameObject triangle(vec4 color);
	static GameObject square(vec4 color);
	static GameObject parallelogram(vec4 color);
};

