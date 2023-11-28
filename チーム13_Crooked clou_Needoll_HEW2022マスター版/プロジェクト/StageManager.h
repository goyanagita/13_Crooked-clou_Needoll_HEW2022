/*****************************************
 * StageManagerヘッダ					 *
 *ステージの管理を行うクラス             *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseStage.h"
class StageManager
{
private:
	BaseStage* NowStage = nullptr;
	BaseStage* NextStage = nullptr;

public:
	StageManager() {};
	~StageManager() {};
	void Init() {};//初期化
	void Uninit() {};//終了処理
	void Update() {};//更新処理
	void Draw() {};//描画処理
	void ChangeStage() {};//ステージ切り替え用関数
};

