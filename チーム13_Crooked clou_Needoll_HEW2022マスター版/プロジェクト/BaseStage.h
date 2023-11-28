/*****************************************
 * BasStageヘッダ				     	 *
 *すべてのステージはこれを継承する       *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
class BaseStage
{
public:
	BaseStage() {};//構築時に自動的に呼ばれる
	~BaseStage() {};//破棄時に自動的に呼ばれる
	void Init() {};//初期化
	void Uninit() {};//終了処理
	void Update() {};//更新処理
	void Draw() {};//描画処理
};

