/*****************************************
 * SceneManagerヘッダ					 *
 *シーンの管理を行うクラス			     *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include"BaseScene.h"
#include"SceneChanger.h"
#include "Game.h"
#include "Title.h"
#include "GameClear.h"
#include "GameOver.h"
class SceneManager:public SceneChanger
{
private:
	BaseScene* m_Scene = nullptr;//シーンの管理変数
	eScene m_NextScene ;//次のシーンの管理変数
	bool game_exit = false;
	bool exit_check = false;
	int stage_info = 0;
	int stage_next = 0;
	bool stage_select = false;
	bool game = false;
	bool stage_clear = false;
public:
	SceneManager() ;//構築時に自動的に呼ばれる
	void Init() ;//初期化
	void Uninit() ;//終了処理
	void Upadate() ;//更新処理
	void Draw() ;//描画処理

	void ChangeScene(eScene NextScene);
	void SetErrorFlag(void) { game_exit = true; }
	bool GetExitFlag(void) { return exit_check; }
	bool GetErrorFlag(void) { return game_exit; }
	//void StageInfo(int stage) { stage_info = stage; }

};

