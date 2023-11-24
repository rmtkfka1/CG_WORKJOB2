#include "pch.h"
#include "SceneManager.h"
#include "fmod.hpp"
#include "fmod_errors.h"

void draw()
{
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::GetInstance()->Render();


	glutSwapBuffers();

};

int main(int argc, char** argv)
{

	Core::GetInstance()->Init(argc, argv);
	Core::GetInstance()->Render(draw);


	KeyManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	MouseManager::GetInstance()->Init();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutSetCursor(GLUT_CURSOR_NONE); // 마우스 커서 숨기기

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

	SceneManager::GetInstance()->ChangeScene(SceneType::Stage1);

	while (1)
	{
		
		

		KeyManager::GetInstance()->Update();
		TimeManager::GetInstance()->Update();
		SceneManager::GetInstance()->Update();

	

		glutPostRedisplay();
		glutMainLoopEvent();
	}

}

