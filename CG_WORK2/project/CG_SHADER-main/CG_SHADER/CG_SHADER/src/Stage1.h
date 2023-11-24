#pragma once

#include "Scene.h"


class Player;
class Model;
class Texture;
class Shader;
class Wall;
class Light;


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


	//���̴�
	Shader* shader;
	//�÷��̾� ��ü
	Player* plane;
	//��

	Model* plane_model;
	Model* wall_model;

	Model* left;
	Model* right;
	Model* front;
	Model* back;
	Model* top;
	Model* blackhole;
	Model* earth;

	//�ؽ���
	Texture* texture;
	Texture* texture2;
	Texture* texture3;
	Texture* texture4;
	//�������
	vector<Wall*> v_wall;

	Light* light;


	int count_hang;
	int count_yal;
	bool pass = false;
	int count = 0;

	bool turn_light = true;

	float testing = 0;

	float temp = 0;
};

