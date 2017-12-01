#pragma once

#include <vector>
#include "vector.h"
#include <iostream>
#include <sstream>
#include <fstream>

class MeshLoader
{
public:
	std::vector <vec3> Vertices, vertexData;
	std::vector <vec2> Texcoords, texcoordData;
	std::vector <vec3> Normals, normalData;
	std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;
	MeshLoader();
	~MeshLoader();
	void parseVertex(std::stringstream& sin);
	void parseTexcoord(std::stringstream& sin);
	void parseNormal(std::stringstream& sin);
	void parseFace(std::stringstream& sin);
	void parseLine(std::stringstream& sin);
	void loadMeshData(std::string& filename);
	void processMeshData();
	void freeMeshData();
	const void createMesh(std::string& filename);
};

