#include "pch.h"
#include "Stage1.h"
#include "Player.h"
#include "Wall.h"
#include "BoxCollider.h"
#include "CollisionManager.h"


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
			cout << "행을 입력해주세요. (5~50 사이의값)" << endl;
			int num = 0;
			cin >> num;
			count_hang = num;
		}

		{
			cout << "열을 입력해주세요. (5~50 사이의값)" << endl;
			int num = 0;
			cin >> num;
			count_yal = num;
		}

		if (count_hang <5 || count_hang >50 || count_yal <5 || count_yal >50 )
		{
			cout << "입력범위를 다시확인해주세요." << endl;
		}
		else
		{
			pass = true;
		}
	}

	

	shader = new Shader("res/shader/mvp.vs", "res/shader/mvp.fs");
	shader->Bind();

	///////////////////////////////////////////////////모델 불러오기 밑에 생성전에 먼저해줘야됨
	
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
			auto trans = matrix::GetInstance()->GetTranslation(i, 0, j);
			box->i = i;
			box->j = j;
			box->matrix = trans * scale;
			v_wall.push_back(box);
		}
	}



	texture = new Texture("res/textures/space2.png");
	texture2 = new Texture("res/textures/space_background.png");

	texture->Bind(0);
	texture2->Bind(1);



	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());


	cout << "===============키보드 입력==================" << endl;
	cout << "1. 각기 다른속도 애니메이션" << endl;
	cout << "2. 파도타기 애니메이션" << endl;
	cout << "3. 나만의 X자 애니메이션" << endl;
	cout << "4.물체의 이동속도 증가" << endl;
	cout << "5.물체의 이동속도 감소" << endl;

	cout << "T. 조명 끄기/켜기" << endl;
	cout << "C. 조명 색 바꾸기" << endl;
	cout << "R. 초기화 하기" << endl;
	cout << "Q. 프로그램 종료 하기" << endl;

	cout << "카메라(공전[Y키]는) 마우스 이동과 WASD 로 대체하였습니다." << endl;


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


	shader->SetUniformMat4f("u_view", CameraManager::GetInstance()->GetMatrix());

	

}

void Stage1::Render()
{
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

	
	}


	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::TWO))
	{
		for (int i = 0; i < count_hang; ++i)
		{
			test += 1.0f;
			for (int j = 0; j < count_yal; ++j)
			{
				v_wall[count_hang*i+j]->dy = 1 + test;
				v_wall[count_hang * i + j]->ChangeAnimation(animation::WAVE_LEFT_ANI);
			}
		}

		test = 0;
	}

	
	if (KeyManager::GetInstance()->GetbuttonDown(KeyType::THREE))
	{
	

		for (int i = 0; i < count_hang; ++i)
		{
			for (int j = 0; j < count_yal; ++j)
			{
				v_wall[count_hang * i + j]->dy = 2.0f;
				v_wall[count_hang * i + j]->speed = 10.0f;
		

			}
		}
		
		for (int i = 0; i < count_hang; ++i) {
			if (i < count_yal) {
				v_wall[i * count_hang + i]->dy = 15.0f;
				v_wall[i * count_hang + i]->speed = 30.0f;
			
		
				v_wall[i * count_hang + (count_hang - 1 - i)]->dy = 15.0f; 
				v_wall[i * count_hang + (count_hang - 1 - i)]->speed = 30.0f;
	
			}
		}

		for (int i = 0; i < v_wall.size(); ++i)
		{
			v_wall[i]->ChangeAnimation(animation::MY_ANI_DOWN);
		}
	}
}
