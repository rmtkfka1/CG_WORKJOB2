#pragma once

#include "Scene.h"


class Player;
class Model;
class Texture;
class Shader;
class Wall;
class Light;
class Light2;

class Stage1 : public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void KeyUpdate();

public:


	//쉐이더
	Shader* shader;
	Shader* shader2;
	//플레이어 객체
	Player* plane;
	//모델

	Model* plane_model;
	Model* wall_model;

	Model* left;
	Model* right;
	Model* front;
	Model* back;
	Model* top;
	Model* blackhole;
	Model* earth;
	Model* sun;

	//텍스쳐
	Texture* texture;
	Texture* texture2;
	Texture* texture3;
	Texture* texture4;
	Texture* texture5;
	Texture* texture6;
	//벽만들기
	vector<Wall*> v_wall;

	Light* light;

	Light2* light2;

	int count_hang;
	int count_yal;
	bool pass = false;
	int count = 0;

	bool turn_light = true;

	float testing = 0;

	float temp = 0;

	bool spot_on = false;
};

