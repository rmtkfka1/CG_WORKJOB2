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
	}

	shader = new Shader("res/shader/mvp.vs", "res/shader/mvp.fs");
	shader->Bind();

	///////////////////////////////////////////////////모델 불러오기 밑에 생성전에 먼저해줘야됨
	
	wall_model = new Model("res/models/box.obj");
	plane_model = new Model("res/models/plane.obj");
	///////////////////////////////////////////////////////////////////////////////////////////



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



	texture = new Texture("res/textures/gold.jpg");
	texture2 = new Texture("res/textures/sea.jpg");

	texture->Bind(0);
	texture2->Bind(1);



	shader->SetUniformMat4f("u_proj", matrix::GetInstance()->GetProjection());


	v_wall[0]->PrintInfo();
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



	for (auto& ele : v_wall)
	{
		shader->SetUniform1i("u_texture", 0);
		ele->Render(*shader, *wall_model, matrix::GetInstance()->GetSimple());
	}

}

void Stage1::KeyUpdate()
{

	if (KeyManager::GetInstance()->Getbutton(KeyType::P))
	{
		//매트릭스를 사이즈와 연산하여
		for (auto& ele : v_wall)
		{
			
			auto scale = matrix::GetInstance()->GetScale(1, ele->dy, 1);
			auto trans = matrix::GetInstance()->GetTranslation(ele->i, 0, ele->j);
			ele->matrix = trans * scale;
			
			ele->dy += 0.01f;
		}
	}
}
