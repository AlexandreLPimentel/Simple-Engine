#include "GameObject.h"
#include "MeshLoader.h"

#define VERTICES 0
#define COLORS 1
#define TEXCOORDS 2
#define NORMALS 3
#define ANIMATIONSPEED 1
#define ANIMATIONEPSILON 0.00001f

GameObject::GameObject()
{
	all_rotation[0] = qtrn::qtrn(1, 0, 0, 0);
	all_rotation[1] = qtrn::qtrn(1, 0, 0, 0);
	all_rotation[2] = qtrn::qtrn(1, 0, 0, 0);
	all_rotation[3] = qtrn::qtrn(1, 0, 0, 0);
	all_translation[0] = mat4::identityMatrix();
	all_translation[1] = mat4::identityMatrix();
	all_translation[2] = mat4::identityMatrix();
	all_translation[3] = mat4::identityMatrix();
	all_scale[0] = mat4::identityMatrix();
	all_scale[1] = mat4::identityMatrix();
	all_scale[2] = mat4::identityMatrix();
	all_scale[3] = mat4::identityMatrix();
	self_rotation[0] = qtrn::qtrn(1, 0, 0, 0);
	self_rotation[1] = qtrn::qtrn(1, 0, 0, 0);
	self_rotation[2] = qtrn::qtrn(1, 0, 0, 0);
	self_rotation[3] = qtrn::qtrn(1, 0, 0, 0);
	self_translation[0] = mat4::identityMatrix();
	self_translation[1] = mat4::identityMatrix();
	self_translation[2] = mat4::identityMatrix();
	self_translation[3] = mat4::identityMatrix();
	self_scale[0] = mat4::identityMatrix();
	self_scale[1] = mat4::identityMatrix();
	self_scale[2] = mat4::identityMatrix();
	self_scale[3] = mat4::identityMatrix();
}

GameObject::~GameObject()
{
}

void GameObject::rotateAll(qtrn rotation, int state)
{
	self_rotation[state] = qtrn::qMultiply(rotation, self_rotation[state]);
	all_rotation[state] = qtrn::qMultiply(rotation, self_rotation[state]);
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
		all_transformation = (all_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(all_rotation[state])) * all_scale[state]);
	}
}

void GameObject::scaleAll(mat4 scale, int state)
{
	self_scale[state] *= scale;
	all_scale[state] *= scale;
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
		all_transformation = (all_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(all_rotation[state])) * all_scale[state]);
	}
}

void GameObject::translateAll(mat4 translation, int state)
{
	self_translation[state] *= translation;
	all_translation[state] *= translation;
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
		all_transformation = (all_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(all_rotation[state])) * all_scale[state]);
	}
}

void GameObject::rotateSelf(qtrn rotation, int state)
{
	self_rotation[state] = qtrn::qMultiply(rotation, self_rotation[state]);
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
	}
}

void GameObject::scaleSelf(mat4 scale, int state)
{
	self_scale[state] *= scale;
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
	}
}

void GameObject::translateSelf(mat4 translation, int state)
{
	self_translation[state] *= translation;
	if (state == 0) {
		self_transformation = (self_translation[state] * *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[state])) * self_scale[state]);
	}
}

GLsizeiptr GameObject::vertexBufferSize() const
{
	return numVertices * sizeof(vertices[0]);
}

GLsizeiptr GameObject::normalBufferSize() const
{
	return numNormals * sizeof(normals[0]);
}

GLsizeiptr GameObject::texCoordsBufferSize() const
{
	return numTexCoords * sizeof(texCoords[0]);
}

mat4* GameObject::draw(GLint ModelMatrix_UId, GLint ViewMatrix_UId, GLint ProjectionMatrix_UId, mat4* parentMatrix)
{
	mat4* modelToDraw, *modelForChildren;
	if (parentMatrix) {
		modelToDraw = new mat4(*parentMatrix * self_transformation);
		modelForChildren = new mat4(*parentMatrix * all_transformation);
	}
	else {
		modelToDraw = new mat4(self_transformation);
		modelForChildren = new mat4(all_transformation);
	}
	glBindVertexArray(VaoId);
	float* model = (*modelToDraw).getColumnMajor();
	float* view = (*ViewMatrix)->getColumnMajor();
	float* projection = (*ProjectionMatrix)->getColumnMajor();
	glUniformMatrix4fv(ModelMatrix_UId, 1, GL_FALSE, model);
	glUniformMatrix4fv(ViewMatrix_UId, 1, GL_FALSE, view);
	glUniformMatrix4fv(ProjectionMatrix_UId, 1, GL_FALSE, projection);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	free(model);
	free(view);
	free(projection);
	return modelForChildren;
}

void GameObject::init(const GLuint UBO_BP) {
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(3, VboId);

		glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize(), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		if (texCoordsLoaded)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
			glBufferData(GL_ARRAY_BUFFER, texCoordsBufferSize(), texCoords, GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);
		}

		if (normalsLoaded)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VboId[2]);
			glBufferData(GL_ARRAY_BUFFER, normalBufferSize(), normals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
		}
	}
}

GameObject GameObject::loadMesh(const std::string& filename) {
	GameObject ret;

	ret.myMeshLoader = new MeshLoader();
	ret.myMeshLoader->createMesh(const_cast<std::string&>(filename));
	ret.normalsLoaded = true /*NORMALSSLOADED*/;
	ret.texCoordsLoaded = false /*TEXCOORDSLOADED*/;
	ret.vertices = &(ret.myMeshLoader->Vertices[0]);
	ret.numVertices = ret.myMeshLoader->Vertices.size();
	if (ret.normalsLoaded) {
		ret.normals = &(ret.myMeshLoader->Normals[0]);
		ret.numNormals = ret.myMeshLoader->Normals.size();
	}
	if (ret.texCoordsLoaded) {
		ret.texCoords = &(ret.myMeshLoader->Texcoords[0]);
		ret.numTexCoords = ret.myMeshLoader->Texcoords.size();
	}
	return ret;
}

void GameObject::runAnimation(int milliseconds) {
	if (!canAnimate || animationDirection == 0.0f)
		return;

	//If we're close enough to the endpoints, stop animating
	if ((animationState < ANIMATIONEPSILON && animationDirection < 0)
		|| (animationState > 3 - ANIMATIONEPSILON && animationDirection > 0)) {
		animationDirection = 0;
		return;
	}

	int before = (int)animationState;
	int after = before + 1;

	float difference = 0.001 * milliseconds * ANIMATIONSPEED * animationDirection;
	float animationPart = animationState - (int)animationState + difference;
	animationState += difference;

	//Update self matrices

	mat4 newSelfTranslation = mat4::identityMatrix();
	float x, y, z, beforeX, afterX, beforeY, afterY, beforeZ, afterZ;
	beforeX = self_translation[before].getCoordinate(0, 3);
	beforeY = self_translation[before].getCoordinate(1, 3);
	beforeZ = self_translation[before].getCoordinate(2, 3);
	afterX = self_translation[after].getCoordinate(0, 3);
	afterY = self_translation[after].getCoordinate(1, 3);
	afterZ = self_translation[after].getCoordinate(2, 3);
	x = beforeX + (afterX - beforeX) * animationPart;
	y = beforeY + (afterY - beforeY) * animationPart;
	z = beforeZ + (afterZ - beforeZ) * animationPart;
	newSelfTranslation.setCoordinate(0, 3, x);
	newSelfTranslation.setCoordinate(1, 3, y);
	newSelfTranslation.setCoordinate(2, 3, z);
	
	mat4 newSelfRotation;
	if (qtrn::qEqual(self_rotation[before], self_rotation[after])) {
		newSelfRotation = *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[before]));
	}
	else {
		qtrn rot = qtrn::qSlerp(self_rotation[before], self_rotation[after], animationPart);
		newSelfRotation = *const_cast<mat4*>(qtrn::qToMatrix(rot));
	}
		
	mat4 newSelfScale = mat4::identityMatrix();
	beforeX = self_scale[before].getCoordinate(0, 0);
	beforeY = self_scale[before].getCoordinate(1, 1);
	beforeZ = self_scale[before].getCoordinate(2, 2);
	afterX = self_scale[after].getCoordinate(0, 0);
	afterY = self_scale[after].getCoordinate(1, 1);
	afterZ = self_scale[after].getCoordinate(2, 2);
	x = beforeX + (afterX - beforeX) * animationPart;
	y = beforeY + (afterY - beforeY) * animationPart;
	z = beforeZ + (afterZ - beforeZ) * animationPart;
	newSelfScale.setCoordinate(0, 0, x);
	newSelfScale.setCoordinate(1, 1, y);
	newSelfScale.setCoordinate(2, 2, z);

	self_transformation = newSelfTranslation * newSelfRotation * newSelfScale;

	//Update matrices affecting children

	mat4 newAllTranslation = mat4::identityMatrix();
	x, y, z, beforeX, afterX, beforeY, afterY, beforeZ, afterZ;
	beforeX = all_translation[before].getCoordinate(0, 3);
	beforeY = all_translation[before].getCoordinate(1, 3);
	beforeZ = all_translation[before].getCoordinate(2, 3);
	afterX = all_translation[after].getCoordinate(0, 3);
	afterY = all_translation[after].getCoordinate(1, 3);
	afterZ = all_translation[after].getCoordinate(2, 3);
	x = beforeX + (afterX - beforeX) * animationPart;
	y = beforeY + (afterY - beforeY) * animationPart;
	z = beforeZ + (afterZ - beforeZ) * animationPart;
	newAllTranslation.setCoordinate(0, 3, x);
	newAllTranslation.setCoordinate(1, 3, y);
	newAllTranslation.setCoordinate(2, 3, z);

	mat4 newAllRotation;
	if (qtrn::qEqual(self_rotation[before], self_rotation[after])) {
		newAllRotation = *const_cast<mat4*>(qtrn::qToMatrix(self_rotation[before]));
	}
	else {
		qtrn rot = qtrn::qSlerp(self_rotation[before], self_rotation[after], animationPart);
		newAllRotation = *const_cast<mat4*>(qtrn::qToMatrix(rot));
	}

	mat4 newAllScale = mat4::identityMatrix();
	beforeX = all_scale[before].getCoordinate(0, 0);
	beforeY = all_scale[before].getCoordinate(1, 1);
	beforeZ = all_scale[before].getCoordinate(2, 2);
	afterX = all_scale[after].getCoordinate(0, 0);
	afterY = all_scale[after].getCoordinate(1, 1);
	afterZ = all_scale[after].getCoordinate(2, 2);
	x = beforeX + (afterX - beforeX) * animationPart;
	y = beforeY + (afterY - beforeY) * animationPart;
	z = beforeZ + (afterZ - beforeZ) * animationPart;
	newAllScale.setCoordinate(0, 0, x);
	newAllScale.setCoordinate(1, 1, y);
	newAllScale.setCoordinate(2, 2, z);

	all_transformation = newAllTranslation * newAllRotation * newAllScale;
}

void GameObject::animate() {
	if (!canAnimate)
		return;
	if (animationDirection == 0.0f) { //If no animation is running, start it
		if (animationState < 1.0f) { //State goes from 0 to 3 and cant stop in the middle
			animationDirection = 1;
		}
		else {
			animationDirection = -1;
		}
	}
	else { //Otherwise reverse it
		animationDirection = -animationDirection;
	}
}


/*
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
		0,1,2,
		5,4,3,
		6,8,9,
		7,6,9,
		11,13,12,
		10,11,12,
		14,16,17,
		14,17,15
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
		0,2,1,
		2,0,3,
		7,4,5,
		5,6,7,
		9,11,10,
		8,9,10,
		13,14,15,
		12,14,13,
		19,16,17,
		16,19,18,
		22,20,23,
		23,20,21
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
		0,2,1,
		2,0,3,
		6,4,5,
		6,7,4,
		8,9,10,
		9,11,10,
		12,13,15,
		12,15,14,
		19,16,17,
		16,19,18,
		20,23,21,
		20,22,23
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

}*/
