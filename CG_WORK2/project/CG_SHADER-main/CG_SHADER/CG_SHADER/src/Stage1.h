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

	//�ؽ���
	Texture* texture;
	Texture* texture2;
	//�������
	vector<Wall*> v_wall;



	int count_hang;
	int count_yal;

	int count = 0;
};

