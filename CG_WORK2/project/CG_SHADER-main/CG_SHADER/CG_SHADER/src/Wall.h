#pragma once

class Model;
#include "Object.h"
class Wall :public Object
{

	using Super = Object;

public:
	Wall(Model& model);
	~Wall();

	void Init() override;
	void Update() override;
	void Render(Shader& shader, Model& model,glm::mat4 matrix) override;
	void SetCenter(glm::vec3 center) { _center = center; }
	void Setsize_y(float y) { _size.y = y; }
	void Setsize(glm::vec3 size) { _size = size; }

	void OnComponentBeginOverlap(Collider* collider, Collider* other) override;
	void OnComponentEndOverlap(Collider* collider, Collider* other) override;

public:
	float dy = 0;
	int i = 0;
	int j = 0;
	bool _collusion = false;

};