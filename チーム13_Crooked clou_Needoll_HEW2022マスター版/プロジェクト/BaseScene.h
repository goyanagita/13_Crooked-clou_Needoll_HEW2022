/*****************************************
 * BasSceneヘッダ			     		 *
 *すべてのシーンはこれを継承する 　　　  *
 *										 *
 *         Auther:ミヤベ＆ウチヤマ		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "SceneChanger.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
class BaseScene
{
protected:
	
	SceneChanger* m_SceneChanger= nullptr;
public:
	BaseScene(SceneChanger* changer);//オブジェクト構築のタイミングで自動的に呼びだされる
	~BaseScene() {};//オブジェクト破棄のタイミング自動的に呼び出される
	virtual void Init() {};//シーンの初期化
	virtual void Uninit() {};//シーンの終了処理
	virtual void Update() {};//シーンの更新処理
	virtual void Draw() {};//シーンの描画処理
	virtual bool ErrorCheck(void) { return false; };
	virtual bool ExitCheck(void) { return false; }
	virtual void  SetStageInfo(int stage) {};
	virtual int GetStage(void) { return -1; };
	virtual bool CheckClear(void) { return false; }
	virtual void SetClear(void) {}
};

