#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::draw(GLint UniformId)
{
	glUniformMatrix4fv(UniformId, 1, GL_TRUE, transformation.getRowMajor());
	glDrawElements(GL_TRIANGLES, indexBufferSize(), GL_UNSIGNED_BYTE, (GLvoid*)0);
}

void GameObject::rotate(mat4 rotation)
{
	transformation *= rotation;
}

void GameObject::scale(mat4 scale)
{
	cout << transformation << endl;
	transformation *= scale;
	cout << transformation << endl;
}

void GameObject::translate(mat4 translation)
{
	transformation *= translation;
}

GLsizeiptr GameObject::wholeVertexBufferSize() const
{
	return numVertices * sizeof(Vertex);
}

GLsizeiptr GameObject::vertexBufferSize() const
{
	return sizeof(vertices[0].XYZW);
}

GLsizeiptr GameObject::colorBufferSize() const
{
	return sizeof(vertices[0].RGBA);
}

GLsizeiptr GameObject::indexBufferSize() const
{
	return numIndices * sizeof(GLubyte);
}

GameObject GameObject::triangle(vec4 color)
{
	GameObject ret;


	Vertex triangle[] =
	{
		{ vec4(0.0f, 0.5f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(-1.0f * SIZE_RATIO, -0.5f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(1.0f * SIZE_RATIO, -0.5f * SIZE_RATIO, 0.0f, 1.0f), color }
	};

	ret.numVertices = sizeof(triangle) / sizeof(*triangle);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, triangle, sizeof(triangle));

	const GLubyte indices[] =
	{
		0,1,2
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

GameObject GameObject::square(vec4 color)
{
	GameObject ret;

		Vertex square[] =
	{
		{ vec4(0.0f, 1.0f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(-1.0f * SIZE_RATIO, 0.0f, 0.0f, 1.0f), color },
		{ vec4(0.0f, -1.0f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(1.0f * SIZE_RATIO, 0.0f, 0.0f, 1.0f), color }
	};

	ret.numVertices = sizeof(square) / sizeof(*square);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, square, sizeof(square));

	const GLubyte indices[] =
	{
		0,1,2,
		2,3,0
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

GameObject GameObject::parallelogram(vec4 color)
{
	GameObject ret;

	Vertex parallelogram[] =
	{
		{ vec4(0.50f * SIZE_RATIO , -0.50f * SIZE_RATIO , 0.0f, 1.0f), color },
		{ vec4(1.50f * SIZE_RATIO, 0.50f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(-0.50f * SIZE_RATIO, 0.50f * SIZE_RATIO, 0.0f, 1.0f), color },
		{ vec4(-1.50f * SIZE_RATIO, -0.50f * SIZE_RATIO, 0.0f, 1.0f), color }
	};

	ret.numVertices = sizeof(parallelogram) / sizeof(*parallelogram);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, parallelogram, sizeof(parallelogram));

	const GLubyte indices[] =
	{
		0,1,2,
		2,3,0


	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}
