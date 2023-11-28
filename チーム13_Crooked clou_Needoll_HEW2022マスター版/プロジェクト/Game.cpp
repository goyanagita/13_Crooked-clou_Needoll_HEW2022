#include "Game.h"
#include "BackGround.h"
#include "CharacterManager.h"
#include "Map.h"
#include "Bullet.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ThreadGauge.h"
#include "Pause.h"
#include "Block.h"
#include "Count.h"
#include "EnemyBullet.h"
#include "BeeBullet.h"
#include "Bridge.h"
#include "Life.h"

#include "input.h"
#include "inputx.h"

#include "fade.h"

//=============================================================================
// ����������
//=============================================================================
void Game::Init()
{
	SceneFadeIn();

	//�{���ǉ�
	InitCount();

	//�Q�[���𓮂����̂ɕK�v�ȃC���X�^���X�̐���
	bg = new BackGround(this);
	om = new ObjectManager(this);
	cm = new CharacterManager(this);
	Map = new MAP(this, m_stage);
	camera = new CAMERA_2D(this);
	bullet = new BULLET(this);	
	tg = new ThreadGauge(this);
	life = new Life(this);
	//�{���ǉ�-------------------------------------------
	ebullet = new ENEMYBULLET(this);
	bbullet = new BEEBULLET(this);
	
	//�C���X�^���X�̏��������Ă�
	bg->InitBG();
	Map->InitMap();
	om->Init();
	bullet->Init();
	cm->Init();
	camera->Init();
	tg->Init();
	life->Init();

	//�{���ǉ�
	ebullet->Init();
	bbullet->Init();
}

//=============================================================================
// �I������
//=============================================================================
void Game::Uninit()
{
	//���������C���X�^���X�Ƃ͋t���ŃC���X�^���X������s��
	if(tg != nullptr){
		delete tg;
		tg = nullptr;
	}
	if (camera != nullptr) {
		delete camera;
		camera = nullptr;

	}
	if (cm != nullptr) {
		cm->Uninit();
		delete cm;
		cm = nullptr;

	}
	if (bullet != nullptr) {
		delete bullet;
		bullet = nullptr;
	}
	if (om != nullptr) {
		om->Uninit();
		delete om;
		om = nullptr;
	}
	if (Map != nullptr) {
		delete Map;
		Map = nullptr;
	}
	//�{���ǉ�-----------------------
	if (ebullet != nullptr) {

		delete ebullet;
		ebullet = nullptr;
	}
	if (bbullet != nullptr) {

		delete bbullet;
		bbullet = nullptr;
	}
	if (life != nullptr) {
		delete life;
		life = nullptr;

	}
	if (bg != nullptr) {
		delete bg;
		bg = nullptr;

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Game::Update()
{
	if((GetKeyboardTrigger(DIK_P)))
	{
		if (pause == nullptr) {
			pause = new Pause;
			pause->Init();
		}
	}
	if (pause != nullptr && pause->GetExitMenu() == true) {
		pause->Uninit();
		delete pause;
		pause = nullptr;
	}
	if (pause == nullptr && goal != true) {
		//�C���X�^���X�̍X�V���s��
		//bg->UpdateBG();
		Map->UpdateMap();
		cm->Update();
		om->Update();
		bullet->Update();
		camera->Update();
		tg->Update();
		error = Map->GetError();

		//�{���ǉ�---------------------
		UpdateCount();
		ebullet->Update();
		bbullet->Update();
		//---------------------------------------
		life->Update();
	}
	else {

		pause->Update();
		
	}
	if ((cm->GetPlayer()->GetPlayerSurv() != true))
		m_SceneChanger->ChangeScene(SceneChanger::eScene::GAMEOVER);
	if (goal)
		m_SceneChanger->ChangeScene(SceneChanger::eScene::GAMECLEAR);


}
//=============================================================================
// �`�揈��
//=============================================================================
void Game::Draw()
{
	//�C���X�^���X�̕`����s��
	bg->DrawBG();
	om->Draw();
	cm->Draw();
	bullet->Draw();
	camera->Draw();
	tg->Draw();
	if (pause != nullptr)
		pause->Draw();

	//�{���ǉ�--------------------------------
	ebullet->Draw();
	bbullet->Draw();
	//---------------------------------------
	life->Draw();
}




/*
 �G�̒e


 �������[

 for(int i = 0;i <100:i++){

 if(�e.GetUse(i) == false){
 �e[i].set(���W�Ƃ������Ƃ�);


*/