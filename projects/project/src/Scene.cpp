#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

SceneNode * Scene::addNode(SceneNode * parent, GameObject *childObject)
{
	SceneNode* newNode = new SceneNode();
	newNode->node = childObject;
	newNode->parent = parent;
	if (parent) {
		parent->children.push_back(newNode);
	}
	else {
		nodeTree = newNode;
	}
	return newNode;
}

void Scene::removeNode(SceneNode* node)
{
	if (!node) { //Return in case the given node is null
		return;
	}
	//If we have a parent, we need to remove ourselves from our parent and give it our children
	if (node->parent) {
		vector<SceneNode*>* parentsChildren = &(node->parent->children);
		parentsChildren->erase(std::remove(parentsChildren->begin(), parentsChildren->end(), node), parentsChildren->end());
		if (node->children.size() > 0) {
			parentsChildren->reserve(parentsChildren->size() + node->children.size());
			parentsChildren->insert(parentsChildren->end(), node->children.begin(), node->children.end());
		}
	}
	//Always give our parent to each of our children
	if (node->children.size() > 0) {
		for (SceneNode* child : node->children) {
			child->parent = node->parent;
		}
	}
	delete node;
}


void Scene::draw(GLint UniformId, GLint ViewMatrix_UId, GLint ProjectionMatrix_UId) {
	nodeTree->draw(UniformId, ViewMatrix_UId, ProjectionMatrix_UId, nullptr);
}

void Scene::animate() {
	nodeTree->animate();
}

void Scene::runAnimation(int milliseconds) {
	nodeTree->runAnimation(milliseconds);
}

