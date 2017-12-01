#pragma once
#include "GameObject.h"
#include <vector>
#include <algorithm>

struct SceneNode {

	GameObject* node;
	vector<SceneNode*> children;
	SceneNode* parent;

	void draw(GLint UniformId, GLint ViewMatrix_UId, GLint ProjectionMatrix_UId, mat4* parentModel) {
		mat4* newModel = node->draw(UniformId, ViewMatrix_UId, ProjectionMatrix_UId, parentModel);
		for (SceneNode* child : children) {
			child->draw(UniformId, ViewMatrix_UId, ProjectionMatrix_UId, newModel);
		}
	}
	void animate() {
		node->animate();
		for (SceneNode* child : children) {
			child->animate();
		}
	}
	void runAnimation(int milliseconds) {
		node->runAnimation(milliseconds);
		for (SceneNode* child : children) {
			child->runAnimation(milliseconds);
		}
	}

};

class Scene
{
private:
	SceneNode* nodeTree;
public:
	Scene();
	~Scene();
	SceneNode* addNode(SceneNode* parent, GameObject *childObject);
	void removeNode(SceneNode* node);
	void draw(GLint UniformId, GLint ViewMatrix_UId, GLint ProjectionMatrix_UId);
	void animate();
	void runAnimation(int milliseconds);
};

