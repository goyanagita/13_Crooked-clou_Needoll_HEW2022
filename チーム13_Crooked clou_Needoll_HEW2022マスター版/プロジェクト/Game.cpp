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
// 初期化処理
//=============================================================================
void Game::Init()
{
	SceneFadeIn();

	//宮部追加
	InitCount();

	//ゲームを動かすのに必要なインスタンスの生成
	bg = new BackGround(this);
	om = new ObjectManager(this);
	cm = new CharacterManager(this);
	Map = new MAP(this, m_stage);
	camera = new CAMERA_2D(this);
	bullet = new BULLET(this);	
	tg = new ThreadGauge(this);
	life = new Life(this);
	//宮部追加-------------------------------------------
	ebullet = new ENEMYBULLET(this);
	bbullet = new BEEBULLET(this);
	
	//インスタンスの初期化を呼ぶ
	bg->InitBG();
	Map->InitMap();
	om->Init();
	bullet->Init();
	cm->Init();
	camera->Init();
	tg->Init();
	life->Init();

	//宮部追加
	ebullet->Init();
	bbullet->Init();
}

//=============================================================================
// 終了処理
//=============================================================================
void Game::Uninit()
{
	//生成したインスタンスとは逆順でインスタンス解放を行う
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
	//宮部追加-----------------------
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
// 更新処理
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
		//インスタンスの更新を行う
		//bg->UpdateBG();
		Map->UpdateMap();
		cm->Update();
		om->Update();
		bullet->Update();
		camera->Update();
		tg->Update();
		error = Map->GetError();

		//宮部追加---------------------
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
// 描画処理
//=============================================================================
void Game::Draw()
{
	//インスタンスの描画を行う
	bg->DrawBG();
	om->Draw();
	cm->Draw();
	bullet->Draw();
	camera->Draw();
	tg->Draw();
	if (pause != nullptr)
		pause->Draw();

	//宮部追加--------------------------------
	ebullet->Draw();
	bbullet->Draw();
	//---------------------------------------
	life->Draw();
}




/*
 敵の弾


 せったー

 for(int i = 0;i <100:i++){

 if(弾.GetUse(i) == false){
 弾[i].set(座標とか向きとか);


*/