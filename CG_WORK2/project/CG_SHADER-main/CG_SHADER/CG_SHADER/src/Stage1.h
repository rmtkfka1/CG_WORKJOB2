#pragma once

#include "Scene.h"


class Player;
class Model;
class Texture;
class Shader;
class Wall;


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

	//텍스쳐
	Texture* texture;
	Texture* texture2;
	//벽만들기
	vector<Wall*> v_wall;



	int count_hang;
	int count_yal;

	int count = 0;
};

