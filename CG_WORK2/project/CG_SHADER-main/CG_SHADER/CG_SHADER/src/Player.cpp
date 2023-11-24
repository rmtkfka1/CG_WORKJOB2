#include "pch.h"
#include "Player.h"
#include "Object.h"
#include "Object.h"
#include "Collider.h"
#include "Model.h"

Player::Player(Model& model):Object(ObjectType::PLAYER)
{
	_center = model.GetCenter();
	_size = model.GetSize();
	_first_center = _center;

}

Player::~Player()
{

}

void Player::Init()
{
	Super::Init();


}

void Player::Update()
{
	

	Super::Update();




}

void Player::Render(Shader& shader,Model& model,glm::mat4 matrix)
{


	shader.SetUniform3f("control_color", _debug_color.x, _debug_color.y, _debug_color.z);
	auto simple = glm::mat4(1.0f);
	shader.SetUniformMat4f("u_model", simple);
	Super::Render(shader,model,matrix);


	shader.SetUniform3f("control_color", 0, 0, 0);
	shader.SetUniformMat4f("u_model", matrix);
	model.RenderModel(shader);


}



void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{

	

	_debug_color.x = 0;
	_debug_color.y = 1;
	_debug_color.z = 0;




}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	

	_debug_color.x = 1;
	_debug_color.y = 0;
	_debug_color.z = 0;

	// 속도 원상복귀
	CameraManager::GetInstance()->m_cameraSpeed = 40.0f;



}
