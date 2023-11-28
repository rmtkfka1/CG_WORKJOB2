#pragma once
#include "Object.h"
class Model;


enum class animation
{
	START_UP_ANI,
	START_DOWN_ANI,
	WAVE_LEFT_ANI,
	WAVE_RIGHT_ANI,
	MY_ANI_DOWN,
	MY_ANI_UP
};

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


	void ChangeAnimation(animation stateinput);
	void UpdateAnimation();
	void UpdateKey();

public:
	float dy = 0;
	int i = 0;
	int j = 0;
	int speed = rand() %70+20;

	bool dontmove = false;

	
	animation state = animation::START_UP_ANI;

};