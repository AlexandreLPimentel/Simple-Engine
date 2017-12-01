#include "MeshLoader.h"



MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
}


void MeshLoader::parseVertex(std::stringstream& sin)
{
	vec3 v;
	sin >> v.data[0] >> v.data[1] >> v.data[2];
	vertexData.push_back(v);
}

void MeshLoader::parseTexcoord(std::stringstream& sin)
{
	vec2 t;
	sin >> t.data[0] >> t.data[1];
	texcoordData.push_back(t);
}

void MeshLoader::parseNormal(std::stringstream& sin)
{
	vec3 n;
	sin >> n.data[0] >> n.data[1] >> n.data[2];
	normalData.push_back(n);
}

void MeshLoader::parseFace(std::stringstream& sin)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) normalIdx.push_back(std::stoi(token));
	}
}

void MeshLoader::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void MeshLoader::loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		parseLine(std::stringstream(line));
	}
}

void MeshLoader::processMeshData()
{
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		vec3 v = vertexData[vi - 1];
		Vertices.push_back(v);
		if (false /*TEXCOORDSLOADED*/) {
			unsigned int ti = texcoordIdx[i];
			vec2 t = texcoordData[ti - 1];
			Texcoords.push_back(t);
		}
		if (true /*NORMALSLOADED*/) {
			unsigned int ni = normalIdx[i];
			vec3 n = normalData[ni - 1];
			Normals.push_back(n);
		}
	}
}

void MeshLoader::freeMeshData()
{
	vertexData.clear();
	texcoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texcoordIdx.clear();
	normalIdx.clear();
}

const void MeshLoader::createMesh(std::string& filename)
{
	loadMeshData(filename);
	processMeshData();
	freeMeshData();
}