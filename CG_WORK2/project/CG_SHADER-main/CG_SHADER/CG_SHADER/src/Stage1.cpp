#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Light.h"
#include "Light2.h"

Stage1::Stage1()
{
	

}

Stage1::~Stage1()
{


}

void Stage1::Init()
{
	/////////////////////// 행열 입력받기///////////////////////////

	while(!pass)
	{
		{
			cout << "행을 입력해주세요. (5~40 사이의값)" << endl;
			int num = 0;
			cin >> num;
			count_hang = num;
		}

		{
			cout << "열을 입력해주세요. (5~40 사이의값)" << endl;
			int num = 0;
			cin >> num;
			count_yal = num;
		}

		if (count_hang <5 || count_hang >40 || count_yal <5 || count_yal >40 )
		{
			cout << "입력범위를 다시확인해주세요." << endl;
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

	result = FMOD::System_Create(&ssystem); //--- 사운드 시스템 생성
	if (result != FMOD_OK)
		exit(0);

	ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata); //--- 사운드 시스템 초기화
	ssystem->createSound("sound.mp3", FMOD_LOOP_NORMAL, 0, &sound1);
	ssystem->playSound(sound1, 0, false, &channel);



	shader = new Shader("res/shader/mvp_new.vs", "res/shader/mvp_new.fs");
	shader->Bind();
	shader2 = new Shader("res/shader/mvp_spotlight.vs", "res/shader/mvp_spotlight.fs");
	shader2->Bind();


	///////////////////////////////////////////////////모델 불러오기 밑에 생성전에 먼저해줘야됨
	
	wall_model = new Model("res/models/box.obj");
	plane_model = new Model("res/models/plane.obj");
	///////////////////////////////////////////////////////////////////////////////////////////

	left = new Model("res/models/box_left.obj");
	right = new Model("res/models/box_right.obj");
	front = new Model("res/models/box_front.obj");
	back = new Model("res/models/box_back.obj");
	top = new Model("res/models/box_top.obj");
	blackhole = new Model("res/models/blackhole.obj");
	earth = new Model("res/models/earth.obj");
	sun = new Model("res/models/sun.obj");

	for(int i=0; i< count_hang; ++i)
	{
		for (int j = 0; j < count_yal; ++j)
		{
			Wall* box = new Wall(*wall_model);
			auto scale =matrix::GetInstance()->GetScale(1,box->dy,1);
			auto trans = matrix::GetInstance()->GetTranslation(i, 0, j);
			box->i = i;
			box->j = j;
			box->matrix = trans * scale;
			v_wall.push_back(box);
		}
	}



	texture = new Texture("res/textures/space2.png");
	texture2 = new Texture("res/textures/space_background.png");
	texture3 = new Texture("res/textures/blackhole.jpg");
	texture4 = new Texture("res/textures/earth.jpg");
	texture5 = new Texture("res/textures/sun.jpg");
	texture6 = new Texture("res/textures/face.png");

	texture6->Bind(5);
	texture->Bind(0);
	texture2->Bind(1);
	texture3->Bind(2);
	texture4->Bind(3);
	texture5->Bind(4);


	

	light = new Light();
	light2 = new Light2();


	cout << "==========================================================" << endl;
	cout << "우주를 컨셉으로 만들어봤슴니당." << endl;
	cout << "==========================================================" << endl;

	cout << "===============키보드 입력==================" << endl;
	cout << "1. 각기 다른속도 애니메이션" << endl;
	cout << "2. 파도타기 애니메이션" << endl;
	cout << "3. 나만의 X자 애니메이션" << endl;
	cout << "4.물체의 이동속도 증가" << endl;
	cout << "5.물체의 이동속도 감소" << endl;

	cout << "T. 조명 끄기/켜기" << endl;
	cout << "C. 조명 색 바꾸기" << endl;
	cout << "R. 초기화 하기" << endl;
	cout << "K. SPOT Light 키기" << endl;
	cout << "Q. 프로그램 종료 하기" << endl;

	cout << "==========================================================" << endl;
	cout << "카메라(공전[Y키]는) 마우스 이동과 WASD 로 대체하였습니다." << endl;
	cout << "==========================================================" << endl;

}

void Stage1::Update()
{




	CameraManager::GetInstance()->KeyUpdate();
	CameraManager::GetInstance()->MouseUpdate(MouseManager::GetInstance()->GetMousePos().x, MouseManager::GetInstance()->GetMousePos().y);



	KeyUpdate();


	for (auto& ele : v_wall)
	{
		ele->Update();
	}

	temp += 10 * TimeManager::GetInstance()->GetDeltaTime();


	

}

void Stage1::Render()
{

	shader->Bind();

	if (spot_on == false)
	{
		{
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 800, 800);
			light->UseLight(*shader);
			shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());
			shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
			shader->SetUniformMat4f("u_model", matrix::GetInstance()->GetSimple());

			if (turn_light)
			{
				light->SetLvector(glm::vec3(69.0f,102.0f,-40.0f));
				light->SetAmbientIntensity(0.01f);
				light->SetDiffuseIntensity(3.0f);
				light->SetSpecularIntensity(3.0f);
				light->SetShinIness(60.0f);
				shader->SetUniform3f("u_eyePosition", CameraManager::GetInstance()->m_cameraPos.x
					, CameraManager::GetInstance()->m_cameraPos.y
					, CameraManager::GetInstance()->m_cameraPos.z);
				light->UseLight(*shader);
			}



			else
			{
				light->SetLvector(glm::vec3(CameraManager::GetInstance()->m_cameraPos.x
					, CameraManager::GetInstance()->m_cameraPos.y
					, CameraManager::GetInstance()->m_cameraPos.z));
				light->SetAmbientIntensity(0.2f);
				light->SetDiffuseIntensity(0);
				light->SetSpecularIntensity(0.1f);
				light->SetShinIness(50);
				shader->SetUniform3f("u_eyePosition", CameraManager::GetInstance()->m_cameraPos.x
					, CameraManager::GetInstance()->m_cameraPos.y
					, CameraManager::GetInstance()->m_cameraPos.z);
				light->UseLight(*shader);

			}

			shader->SetUniform3f("u_eyePosition", CameraManager::GetInstance()->m_cameraPos.x
				, CameraManager::GetInstance()->m_cameraPos.y
				, CameraManager::GetInstance()->m_cameraPos.z);
		
			light->SetAmbientIntensity(7.0f);
			light->UseLight(*shader);
			shader->SetUniform1i("u_texture", 4);
			sun->RenderModel(*shader);

			light->SetAmbientIntensity(0.2f);
			light->UseLight(*shader);
			shader->SetUniform1i("u_texture", 1);

			plane_model->RenderModel(*shader);
			left->RenderModel(*shader);
			right->RenderModel(*shader);
			front->RenderModel(*shader);
			back->RenderModel(*shader);
			top->RenderModel(*shader);

			shader->SetUniform1i("u_texture", 3);
			shader->SetUniformMat4f("u_model", matrix::GetInstance()->GetRotate(temp, 0, 1, 0));
			earth->RenderModel(*shader);


			{
				auto trans = matrix::GetInstance()->GetTranslation(-blackhole->GetCenter().x, -blackhole->GetCenter().y, -blackhole->GetCenter().z);
				auto rotate = matrix::GetInstance()->GetRotate(temp, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation(blackhole->GetCenter().x, blackhole->GetCenter().y, blackhole->GetCenter().z);
				shader->SetUniformMat4f("u_model", trans2 * rotate * trans);
				shader->SetUniform1i("u_texture", 2);
				blackhole->RenderModel(*shader);

			}

			for (auto& ele : v_wall)
			{
				shader->SetUniform1i("u_texture", 0);
				ele->Render(*shader, *wall_model, matrix::GetInstance()->GetSimple());
			}
		}

		{
			glDisable(GL_DEPTH_TEST);

			glViewport(600, 600, 200, 200);

			shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());
			auto view = glm::lookAt(
				glm::vec3(14.4149f, 78.1575f, 27.9546f),
				glm::vec3(14.4149f - 0.00128137f, 78.1575f + -0.980925f, 27.9546f - 0.194382f),
				glm::vec3(0, 1, 0));
			shader->SetUniformMat4f("u_view", view);
			glm::mat4 projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.0f, 100.0f);
			shader->SetUniformMat4f("u_proj", projection);

			shader->SetUniform1i("u_texture", 3);
			earth->RenderModel(*shader);

			shader->SetUniform1i("u_texture", 2);
			blackhole->RenderModel(*shader);

			shader->SetUniform1i("u_texture", 1);
			shader->SetUniformMat4f("u_model", matrix::GetInstance()->GetSimple());

			plane_model->RenderModel(*shader);
			left->RenderModel(*shader);
			right->RenderModel(*shader);
			front->RenderModel(*shader);
			back->RenderModel(*shader);
			top->RenderModel(*shader);
			blackhole->RenderModel(*shader);


			{
				auto trans = matrix::GetInstance()->GetTranslation(-blackhole->GetCenter().x, -blackhole->GetCenter().y, -blackhole->GetCenter().z);
				auto rotate = matrix::GetInstance()->GetRotate(temp, 0, 1, 0);
				auto trans2 = matrix::GetInstance()->GetTranslation(blackhole->GetCenter().x, blackhole->GetCenter().y, blackhole->GetCenter().z);
				shader->SetUniformMat4f("u_model", trans2 * rotate * trans);
				shader->SetUniform1i("u_texture", 2);
				blackhole->RenderModel(*shader);

			}
			for (auto& ele : v_wall)
			{
				shader->SetUniform1i("u_texture", 0);
				ele->Render(*shader, *wall_model, matrix::GetInstance()->GetSimple());
			}
		}

	}

	
	else
	{
		shader2->Bind();
		light2->UseLight(*shader2);

		light2->_light.position = CameraManager::GetInstance()->m_cameraPos;
		light2->_light.direction = CameraManager::GetInstance()->m_cameraFront;


		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, 800, 800);

		shader2->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());
		shader2->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());
		shader2->SetUniformMat4f("u_model", matrix::GetInstance()->GetSimple());


		if (turn_light)
		{

			shader2->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x
				, CameraManager::GetInstance()->m_cameraPos.y
				, CameraManager::GetInstance()->m_cameraPos.z);



		}

		else
		{

			shader2->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x
				, CameraManager::GetInstance()->m_cameraPos.y
				, CameraManager::GetInstance()->m_cameraPos.z);
			light2->UseLight(*shader2);

		}

		shader2->SetUniform3f("u_viewpos", CameraManager::GetInstance()->m_cameraPos.x
			, CameraManager::GetInstance()->m_cameraPos.y
			, CameraManager::GetInstance()->m_cameraPos.z);
		shader2->SetUniform1i("u_texture", 4);

		light2->_light.ambient = glm::vec3(100.0f, 100.0f, 100.0f);
		sun->RenderModel(*shader2);
		light2->_light.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		light2->UseLight(*shader2);
		shader2->SetUniform1i("u_texture", 1);
		plane_model->RenderModel(*shader2);
		left->RenderModel(*shader2);
		right->RenderModel(*shader2);
		front->RenderModel(*shader2);
		back->RenderModel(*shader2);
		top->RenderModel(*shader2);

		shader2->SetUniform1i("u_texture", 3);
		shader2->SetUniformMat4f("u_model", matrix::GetInstance()->GetRotate(temp, 0, 1, 0));
		earth->RenderModel(*shader2);


		{
			auto trans = matrix::GetInstance()->GetTranslation(-blackhole->GetCenter().x, -blackhole->GetCenter().y, -blackhole->GetCenter().z);
			auto rotate = matrix::GetInstance()->GetRotate(temp, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(blackhole->GetCenter().x, blackhole->GetCenter().y, blackhole->GetCenter().z);
			shader2->SetUniformMat4f("u_model", trans2 * rotate * trans);
			shader2->SetUniform1i("u_texture", 2);
			blackhole->RenderModel(*shader2);
		}

		for (auto& ele : v_wall)
		{
			shader2->SetUniform1i("u_texture", 0);
			ele->Render(*shader2, *wall_model, matrix::GetInstance()->GetSimple());
		}
	}

	{
		glDisable(GL_DEPTH_TEST);

		glViewport(600, 600, 200, 200);

		shader2->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());
		auto view = glm::lookAt(
			glm::vec3(14.4149f, 78.1575f, 27.9546f),
			glm::vec3(14.4149f - 0.00128137f, 78.1575f + -0.980925f, 27.9546f - 0.194382f),
			glm::vec3(0, 1, 0));
		shader2->SetUniformMat4f("u_view", view);
		glm::mat4 projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.0f, 100.0f);
		shader2->SetUniformMat4f("u_proj", projection);

		shader2->SetUniform1i("u_texture", 3);
		earth->RenderModel(*shader2);

		shader2->SetUniform1i("u_texture", 2);
		blackhole->RenderModel(*shader2);

		shader2->SetUniform1i("u_texture", 1);
		shader2->SetUniformMat4f("u_model", matrix::GetInstance()->GetSimple());

		plane_model->RenderModel(*shader2);
		left->RenderModel(*shader2);
		right->RenderModel(*shader2);
		front->RenderModel(*shader2);
		back->RenderModel(*shader2);
		top->RenderModel(*shader2);
		blackhole->RenderModel(*shader2);


		{
			auto trans = matrix::GetInstance()->GetTranslation(-blackhole->GetCenter().x, -blackhole->GetCenter().y, -blackhole->GetCenter().z);
			auto rotate = matrix::GetInstance()->GetRotate(temp, 0, 1, 0);
			auto trans2 = matrix::GetInstance()->GetTranslation(blackhole->GetCenter().x, blackhole->GetCenter().y, blackhole->GetCenter().z);
			shader2->SetUniformMat4f("u_model", trans2 * rotate * trans);
			shader2->SetUniform1i("u_texture", 2);
			blackhole->RenderModel(*shader2);

		}
		for (auto& ele : v_wall)
		{
			shader2->SetUniform1i("u_texture", 0);
			ele->Render(*shader2, *wall_model, matrix::GetInstance()->GetSimple());
		}
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
				v_wall[count_hang * i + j]->speed = 20.0f;
		

			}
		}
		
		for (int i = 0; i < count_hang; ++i) {
			if (i < count_yal) {
				v_wall[i * count_hang + i]->dy = 30.0f;
				v_wall[i * count_hang + i]->speed = 60.0f;
			
		
				v_wall[i * count_hang + (count_hang - 1 - i)]->dy = 30.0f;
				v_wall[i * count_hang + (count_hang - 1 - i)]->speed = 60.0f;
	
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
		if (spot_on == false)
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

		else
		{
			static int count2 = 0;
		

		

			if (count2 % 4 == 0)
			{

				light2->_light.diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
				count2++;
				return;
			}

			if (count2 % 4 == 1)
			{
				light2->_light.diffuse = glm::vec3(10.0f, 0, 0);
				count2++;
				return;
			}

			if (count2 % 4 == 2)
			{
				light2->_light.diffuse = glm::vec3(0, 10.0f, 0);
				count2++;
				return;
			}

			if (count2 % 4 == 3)
			{
				light2->_light.diffuse = glm::vec3(0, 0, 10.0f);
				count2++;
				return;
			}



		}
	
	}
	if (KeyManager::GetInstance()->Getbutton(KeyType::R))
	{


	
		pass = false;

		while (!pass)
		{
			{
				cout << "행을 입력해주세요. (5~40 사이의값)" << endl;
				int num = 0;
				cin >> num;
				count_hang = num;
			}

			{
				cout << "열을 입력해주세요. (5~40 사이의값)" << endl;
				int num = 0;
				cin >> num;
				count_yal = num;
			}

			if (count_hang < 5 || count_hang >40 || count_yal < 5 || count_yal >40)
			{
				cout << "입력범위를 다시확인해주세요." << endl;
			}
			else
			{
				pass = true;
			}
		}

		//메모리제거//

		for (int i = 0; i < v_wall.size(); ++i)
		{
			delete v_wall[i];
		}

		v_wall.clear();


		for (int i = 0; i < count_hang; ++i)
		{
			for (int j = 0; j < count_yal; ++j)
			{
				Wall* box = new Wall(*wall_model);
				auto scale = matrix::GetInstance()->GetScale(1, box->dy, 1);
				auto trans = matrix::GetInstance()->GetTranslation(i, 0, j);
				box->i = i;
				box->j = j;
				box->matrix = trans * scale;
				v_wall.push_back(box);
			}
		}


	

			CameraManager::GetInstance()->m_cameraPos = glm::vec3(0, 10.0f, 100.0f);
			CameraManager::GetInstance()->m_cameraFront= glm::vec3(0.0f,0.0f,-1.0f);
			CameraManager::GetInstance()->m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	}

	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::Q))
	{
		exit(0);
	}

	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::K))
	{
		spot_on = !spot_on;
	}


}

