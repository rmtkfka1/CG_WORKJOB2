#include "pch.h"
#include "Wall.h"
#include "Model.h"

Wall::Wall(Model& model) :Object(ObjectType::WALL)
{
	_center = model.GetCenter();

	_size = model.GetSize();
	_first_center = _center;
	_first_size = _size;



}

Wall::~Wall()
{

}

void Wall::Init()
{
	Super::Init();


}

void Wall::Update()
{
	Super::Update();

	UpdateAnimation();

}

void Wall::Render(Shader& shader, Model& model, glm::mat4 matrix2)
{


	//shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	//auto simple = glm::mat4(1.0f);
	//shader.SetUniformMat4f("u_model", simple);
	//Super::Render(shader, model, matrix2);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", this->matrix);
	model.RenderModel(shader);


}

void Wall::OnComponentBeginOverlap(Collider* collider, Collider* other)
{




	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;




}

void Wall::OnComponentEndOverlap(Collider* collider, Collider* other)
{


	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;



}

void Wall::ChangeAnimation(animation stateinput)
{
	switch (state)
	{
	case animation::START_UP_ANI:
		break;
	case animation::START_DOWN_ANI:
		break;
	case animation::WAVE_LEFT_ANI:
		break;
	default:
		break;
	}

	state = stateinput;


}

void Wall::UpdateAnimation()
{

	switch (state)
	{
	case animation::START_UP_ANI:
	{
		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		this->dy += 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();

		if (this->dy > 20.0f)
		{
			ChangeAnimation(animation::START_DOWN_ANI);
		}
	}
		break;

	case animation::START_DOWN_ANI:
	{
		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		this->dy -= 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();

		if (this->dy < 1.0f)
		{
			ChangeAnimation(animation::START_UP_ANI);
		}
	}
		break;
	case animation::WAVE_LEFT_ANI:
	{
		this->speed = 50.0f;
		this->dy -= 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();

		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		if (this->dy < 1.0f)
		{
			ChangeAnimation(animation::WAVE_RIGHT_ANI);
		}
	}
	break;

	case animation::WAVE_RIGHT_ANI:
	{
		this->speed = 50.0f;
		this->dy += 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();

		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		if (this->dy >20.0f)
		{
			ChangeAnimation(animation::WAVE_LEFT_ANI);
		}
	}
	break;
	case animation::MY_ANI_DOWN:
	{
	
		this->dy -= 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();
		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		if (this->dy < 1.0f)
		{
			ChangeAnimation(animation::MY_ANI_UP);
		}

	}
	break;

	case animation::MY_ANI_UP:
	{
		this->dy += 0.1 * this->speed * TimeManager::GetInstance()->GetDeltaTime();
		auto scale = matrix::GetInstance()->GetScale(1, this->dy, 1);
		auto trans = matrix::GetInstance()->GetTranslation(this->i, 0, this->j);
		this->matrix = trans * scale;

		if (this->dy > 20.0f)
		{
			ChangeAnimation(animation::MY_ANI_DOWN);
		}
	}
	break;
	default:

		break;
	}

}


