#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::draw(GLint UniformId)
{
	glBindBuffer(GL_UNIFORM_BUFFER, VboId[2]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), ViewMatrix->getColumnMajor());
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), (*ProjectionMatrix)->getColumnMajor());
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindVertexArray(VaoId);

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transformation.getColumnMajor());
	glDrawElements(GL_TRIANGLES, indexBufferSize(), GL_UNSIGNED_BYTE, (GLvoid*)0);
}

void GameObject::rotate(mat4 rotation)
{
	transformation *= rotation;
}

void GameObject::scale(mat4 scale)
{
	transformation *= scale;
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

GameObject GameObject::triangle(vec4 color, float depth)
{
	GameObject ret;

	vec4* colors = generateColors(color);

	Vertex triangle[] =
	{
		{ vec4(0.0f, 0.5f, depth, 1.0f), colors[0] },
		{ vec4(-1.0f, -0.5f, depth, 1.0f), colors[0] },
		{ vec4(1.0f, -0.5f, depth, 1.0f), colors[0] },

		{ vec4(0.0f, 0.5f, -depth, 1.0f), colors[1] },
		{ vec4(-1.0f, -0.5f, -depth, 1.0f), colors[1] },
		{ vec4(1.0f, -0.5f, -depth, 1.0f), colors[1] },

		{ vec4(-1.0f, -0.5f, depth, 1.0f), colors[2] },
		{ vec4(1.0f, -0.5f, depth, 1.0f), colors[2] },
		{ vec4(-1.0f, -0.5f, -depth, 1.0f), colors[2] },
		{ vec4(1.0f, -0.5f, -depth, 1.0f), colors[2] },

		{ vec4(0.0f, 0.5f, depth, 1.0f), colors[3] },
		{ vec4(1.0f, -0.5f, depth, 1.0f), colors[3] },
		{ vec4(0.0f, 0.5f, -depth, 1.0f), colors[3] },
		{ vec4(1.0f, -0.5f, -depth, 1.0f), colors[3] },

		{ vec4(0.0f, 0.5f, depth, 1.0f), colors[4] },
		{ vec4(-1.0f, -0.5f, depth, 1.0f), colors[4] },
		{ vec4(0.0f, 0.5f, -depth, 1.0f), colors[4] },
		{ vec4(-1.0f, -0.5f, -depth, 1.0f), colors[4] }
	};


	ret.numVertices = sizeof(triangle) / sizeof(*triangle);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, triangle, sizeof(triangle));

	const GLubyte indices[] =
	{
		0,2,1,
		5,3,4,
		6,9,8,
		7,9,6,
		11,12,13,
		10,12,11,
		14,17,16,
		14,15,17
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

GameObject GameObject::square(vec4 color, float depth)
{
	GameObject ret;

	vec4* colors = generateColors(color);

	Vertex square[] =
	{
		//0123
		{ vec4(0.0f, 1.0f, -depth, 1.0f), colors[0] },
		{ vec4(-1.0f, 0.0f, -depth, 1.0f), colors[0] },
		{ vec4(0.0f, -1.0f, -depth, 1.0f), colors[0] },
		{ vec4(1.0f, 0.0f, -depth, 1.0f), colors[0] },

		//4567
		{ vec4(0.0f, 1.0f, depth, 1.0f), colors[1] },
		{ vec4(-1.0f, 0.0f, depth, 1.0f), colors[1] },
		{ vec4(0.0f, -1.0f, depth, 1.0f), colors[1] },
		{ vec4(1.0f, 0.0f, depth, 1.0f), colors[1] },

		//0145 -> 891011
		{ vec4(0.0f, 1.0f, -depth, 1.0f), colors[2] },
		{ vec4(-1.0f, 0.0f, -depth, 1.0f), colors[2] },
		{ vec4(0.0f, 1.0f, depth, 1.0f), colors[2] },
		{ vec4(-1.0f, 0.0f, depth, 1.0f), colors[2] },

		//0347 -> 12131415
		{ vec4(0.0f, 1.0f, -depth, 1.0f), colors[3] },
		{ vec4(1.0f, 0.0f, -depth, 1.0f), colors[3] },
		{ vec4(0.0f, 1.0f, depth, 1.0f), colors[3] },
		{ vec4(1.0f, 0.0f, depth, 1.0f), colors[3] },

		//1256 -> 16171819
		{ vec4(-1.0f, 0.0f, -depth, 1.0f), colors[4] },
		{ vec4(0.0f, -1.0f, -depth, 1.0f), colors[4] },
		{ vec4(-1.0f, 0.0f, depth, 1.0f), colors[4] },
		{ vec4(0.0f, -1.0f, depth, 1.0f), colors[4] },

		//2367 ->20212223
		{ vec4(0.0f, -1.0f, -depth, 1.0f), colors[5] },
		{ vec4(1.0f, 0.0f, -depth, 1.0f), colors[5] },
		{ vec4(0.0f, -1.0f, depth, 1.0f), colors[5] },
		{ vec4(1.0f, 0.0f, depth, 1.0f), colors[5] }
	};

	ret.numVertices = sizeof(square) / sizeof(*square);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, square, sizeof(square));

	const GLubyte indices[] =
	{
		0,1,2,
		2,3,0,
		7,5,4,
		5,7,6,
		9,10,11,
		8,10,9,
		13,15,14,
		12,13,14,
		19,17,16,
		16,18,19,
		22,23,20,
		23,21,20
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

GameObject GameObject::parallelogram(vec4 color, float depth)
{
	GameObject ret;

	vec4* colors = generateColors(color);

	Vertex parallelogram[] =
	{
		//0123
		{ vec4(0.50f , -0.50f , -depth, 1.0f), colors[0] },
		{ vec4(1.50f, 0.50f, -depth, 1.0f), colors[0] },
		{ vec4(-0.50f, 0.50f, -depth, 1.0f), colors[0] },
		{ vec4(-1.50f, -0.50f, -depth, 1.0f), colors[0] },

		//4567
		{ vec4(0.50f , -0.50f , depth, 1.0f), colors[1] },
		{ vec4(1.50f, 0.50f, depth, 1.0f), colors[1] },
		{ vec4(-0.50f, 0.50f, depth, 1.0f), colors[1] },
		{ vec4(-1.50f, -0.50f, depth, 1.0f), colors[1] },

		//0145 -> 891011
		{ vec4(0.50f , -0.50f , -depth, 1.0f), colors[2] },
		{ vec4(1.50f, 0.50f, -depth, 1.0f), colors[2] },
		{ vec4(0.50f , -0.50f , depth, 1.0f), colors[2] },
		{ vec4(1.50f, 0.50f, depth, 1.0f), colors[2] },

		//2367 -> 12131415
		{ vec4(-0.50f, 0.50f, -depth, 1.0f), colors[3] },
		{ vec4(-1.50f, -0.50f, -depth, 1.0f), colors[3] },
		{ vec4(-0.50f, 0.50f, depth, 1.0f), colors[3] },
		{ vec4(-1.50f, -0.50f, depth, 1.0f), colors[3] },

		//1256 -> 16171819
		{ vec4(1.50f, 0.50f, -depth, 1.0f), colors[4] },
		{ vec4(-0.50f, 0.50f, -depth, 1.0f), colors[4] },
		{ vec4(1.50f, 0.50f, depth, 1.0f), colors[4] },
		{ vec4(-0.50f, 0.50f, depth, 1.0f), colors[4] },

		//0347 -> 20212223
		{ vec4(0.50f , -0.50f , -depth, 1.0f), colors[5] },
		{ vec4(-1.50f, -0.50f, -depth, 1.0f), colors[5] },
		{ vec4(0.50f , -0.50f , depth, 1.0f), colors[5] },
		{ vec4(-1.50f, -0.50f, depth, 1.0f), colors[5] }
	};

	ret.numVertices = sizeof(parallelogram) / sizeof(*parallelogram);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, parallelogram, sizeof(parallelogram));

	const GLubyte indices[] =
	{
		0,1,2,
		2,3,0,
		6,5,4,
		6,4,7,
		8,10,9,
		9,10,11,
		12,15,13,
		12,14,15,
		19,17,16,
		16,18,19,
		20,21,23,
		20,23,22
	};

	ret.numIndices = sizeof(indices) / sizeof(*indices);
	ret.indices = new GLubyte[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

vec4 * GameObject::generateColors(vec4 source)
{
	rgb original = rgb();
	original.r = source.getX();
	original.g = source.getY();
	original.b = source.getZ();
	hsv transformed = rgb2hsv(original);
	hsv c1 = hsv(transformed);
	hsv c2 = hsv(transformed);
	hsv c3 = hsv(transformed);
	hsv c4 = hsv(transformed);
	hsv c5 = hsv(transformed);
	hsv c6 = hsv(transformed);
	hsv c7 = hsv(transformed);
	hsv c8 = hsv(transformed);
	hsv c9 = hsv(transformed);

	c1.s = c1.s*0.9;
	c2.s = c2.s*0.8;
	c3.s = c3.s*0.7;
	c4.s = c4.s*0.6;
	c5.s = c5.s*0.5;
	c6.s = c6.s*0.4;
	c7.s = c7.s*0.3;
	c8.s = c8.s*0.2;
	c9.s = c9.s*0.1;

	c9.v = c9.v*0.1;
	c8.v = c8.v*0.2;
	c7.v = c7.v*0.3;
	c6.v = c6.v*0.4;
	c5.v = c5.v*0.5;
	c4.v = c4.v*0.6;
	c3.v = c3.v*0.7;
	c2.v = c2.v*0.8;
	c1.v = c1.v*0.9;

	rgb r1 = hsv2rgb(c1);
	rgb r2 = hsv2rgb(c2);
	rgb r3 = hsv2rgb(c3);
	rgb r4 = hsv2rgb(c4);
	rgb r5 = hsv2rgb(c5);
	rgb r6 = hsv2rgb(c6);
	rgb r7 = hsv2rgb(c7);
	rgb r8 = hsv2rgb(c8);
	rgb r9 = hsv2rgb(c9);

	vec4 ret[] = {
		vec4(r1.r, r1.g, r1.b, 1),
		vec4(r2.r, r2.g, r2.b, 1),
		vec4(r3.r, r3.g, r3.b, 1),
		vec4(r4.r, r4.g, r4.b, 1),
		vec4(r5.r, r5.g, r5.b, 1),
		vec4(r6.r, r6.g, r6.b, 1),
		vec4(r7.r, r7.g, r7.b, 1),
		vec4(r8.r, r8.g, r9.b, 1),
		vec4(r9.r, r9.g, r8.b, 1)
	};

	return ret;

}
