#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Light.h"


Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{
	/////////////////////// �࿭ �Է¹ޱ�///////////////////////////

	while(!pass)
	{
		{
			cout << "���� �Է����ּ���. (5~50 �����ǰ�)" << endl;
			int num = 0;
			cin >> num;
			count_hang = num;
		}

		{
			cout << "���� �Է����ּ���. (5~50 �����ǰ�)" << endl;
			int num = 0;
			cin >> num;
			count_yal = num;
		}

		if (count_hang <5 || count_hang >50 || count_yal <5 || count_yal >50 )
		{
			cout << "�Է¹����� �ٽ�Ȯ�����ּ���." << endl;
		}
		else
		{
			pass = true;
		}
	}

	
	FMOD::System* ssystem;
	FMOD::Sound* sound1, * sound2;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;

	result = FMOD::System_Create(&ssystem); //--- ���� �ý��� ����
	if (result != FMOD_OK)
		exit(0);

	ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata); //--- ���� �ý��� �ʱ�ȭ
	ssystem->createSound("sound.mp3", FMOD_LOOP_NORMAL, 0, &sound1);
	ssystem->playSound(sound1, 0, false, &channel);



	shader = new Shader("res/shader/mvp_new.vs", "res/shader/mvp_new.fs");
	shader->Bind();

	///////////////////////////////////////////////////�� �ҷ����� �ؿ� �������� ��������ߵ�
	
	wall_model = new Model("res/models/box.obj");
	plane_model = new Model("res/models/plane.obj");
	///////////////////////////////////////////////////////////////////////////////////////////

	left = new Model("res/models/box_left.obj");
	right = new Model("res/models/box_right.obj");
	front = new Model("res/models/box_front.obj");
	back = new Model("res/models/box_back.obj");
	top = new Model("res/models/box_top.obj");

	for(int i=0; i< count_hang; ++i)
	{
		for (int j = 0; j < count_yal; ++j)
		{
			Wall* box = new Wall(*wall_model);
			auto scale =matrix::GetInstance()->GetScale(1,box->dy,1);
			auto trans = matrix::GetInstance()->GetTranslation(i, 0, j+20);
			box->i = i;
			box->j = j+20;
			box->matrix = trans * scale;
			v_wall.push_back(box);
		}
	}



	texture = new Texture("res/textures/space2.png");
	texture2 = new Texture("res/textures/space_background.png");

	texture->Bind(0);
	texture2->Bind(1);



	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());

	light = new Light();



	cout << "==========================================================" << endl;
	cout << "���ָ� ǥ���غ��ҽ��ϴ�." << endl;
	cout << "==========================================================" << endl;

	cout << "===============Ű���� �Է�==================" << endl;
	cout << "1. ���� �ٸ��ӵ� �ִϸ��̼�" << endl;
	cout << "2. �ĵ�Ÿ�� �ִϸ��̼�" << endl;
	cout << "3. ������ X�� �ִϸ��̼�" << endl;
	cout << "4.��ü�� �̵��ӵ� ����" << endl;
	cout << "5.��ü�� �̵��ӵ� ����" << endl;

	cout << "T. ���� ����/�ѱ�" << endl;
	cout << "C. ���� �� �ٲٱ�" << endl;
	cout << "R. �ʱ�ȭ �ϱ�" << endl;
	cout << "Q. ���α׷� ���� �ϱ�" << endl;

	cout << "==========================================================" << endl;
	cout << "ī�޶�(����[YŰ]��) ���콺 �̵��� WASD �� ��ü�Ͽ����ϴ�." << endl;
	cout << "==========================================================" << endl;

}

void Stage1::Update()
{




	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);



	KeyUpdate();
	LightUpdate();

	for (auto& ele : v_wall)
	{
		ele->Update();
	}


	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	

}

void Stage1::Render()
{


	light->UseLight(*shader);

	shader->SetUniform1i("u_texture", 1);
	shader->SetUniformMat4f("u_model", matrix::GetInstance()->GetSimple());
	plane_model->RenderModel(*shader);

	left->RenderModel(*shader);
	right->RenderModel(*shader);
	front->RenderModel(*shader);
	back->RenderModel(*shader);
	top->RenderModel(*shader);
	for (auto& ele : v_wall)
	{
		shader->SetUniform1i("u_texture", 0);
		ele->Render(*shader, *wall_model, matrix::GetInstance()->GetSimple());
	}

}

void Stage1::KeyUpdate()
{
	static float test = 0;

	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::ONE))
	{
		for (int i = 0; i < v_wall.size(); ++i)
		{
			v_wall[i]->dy = 1.0f;
			v_wall[i]->speed = rand() % 70 + 20;

			v_wall[i]->ChangeAnimation(animation::START_UP_ANI);
		}

		test = 0;
	
	}


	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::TWO))
	{

		for (int i = 0; i < v_wall.size(); ++i)
		{
			v_wall[i]->dy = 1.0f;
		
		}


		for (int i = 0; i < count_hang; ++i)
		{
			test += 1.0f;
			for (int j = 0; j < count_yal; ++j)
			{
				v_wall[count_hang*i+j]->dy = 1 + test;
				v_wall[count_hang * i + j]->ChangeAnimation(animation::WAVE_LEFT_ANI);
			}
		}


		for (int i = 0; i < v_wall.size(); ++i)
		{
			v_wall[i]->ChangeAnimation(animation::WAVE_LEFT_ANI);

		}

	}

	
	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::THREE))
	{
	

		for (int i = 0; i < count_hang; ++i)
		{
			for (int j = 0; j < count_yal; ++j)
			{
				v_wall[count_hang * i + j]->dy = 2.0f;
				v_wall[count_hang * i + j]->speed = 100.0f;
		

			}
		}
		
		for (int i = 0; i < count_hang; ++i) {
			if (i < count_yal) {
				v_wall[i * count_hang + i]->dy = 70.0f;
				v_wall[i * count_hang + i]->speed = 100.0f;
			
		
				v_wall[i * count_hang + (count_hang - 1 - i)]->dy = 70.0f; 
				v_wall[i * count_hang + (count_hang - 1 - i)]->speed = 100.0f;
	
			}
		}

		for (int i = 0; i < v_wall.size(); ++i)
		{
			v_wall[i]->ChangeAnimation(animation::MY_ANI_DOWN);
		}
	}

	if(KeyManager::GetInstance()->GetbuttonDown(KeyType::T))
	{
		turn_light = !turn_light;
	}

	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::C))
	{
		static int count = 0;

		count++;

		if (count % 4 == 0)
		{
			light->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
		}

		if (count % 4 == 1)
		{
			light->SetLightColor(glm::vec3(1.0f, 0, 0));
			return;
		}

		if (count % 4 == 2)
		{
			light->SetLightColor(glm::vec3(0, 1.0f, 0));
			return;
		}

		if (count % 4 == 3)
		{
			light->SetLightColor(glm::vec3(0, 0, 1.0f));
			return;
		}
	
	}
}

void Stage1::LightUpdate()
{

	if (turn_light)
	{
		light->SetLvector(glm::vec3(CameraManager::GetInstance()->m_cameraPos.x, CameraManager::GetInstance()->m_cameraPos.y, CameraManager::GetInstance()->m_cameraPos.z));
		//light->SetLvector(glm::vec3(0,1,0));
		light->SetAmbientIntensity(0.3f);
		light->SetDiffuseIntensity(5.0f);
		light->SetSpecularIntensity(15.0f);
		light->SetShinIness(10.0f);
		shader->SetUniform3f("u_eyePosition", CameraManager::GetInstance()->m_cameraPos.x
			, CameraManager::GetInstance()->m_cameraPos.y
			, CameraManager::GetInstance()->m_cameraPos.z);

	}
	else
	{
		light->SetAmbientIntensity(0.3f);
		light->SetDiffuseIntensity(0);
		light->SetSpecularIntensity(0);
	}
}
