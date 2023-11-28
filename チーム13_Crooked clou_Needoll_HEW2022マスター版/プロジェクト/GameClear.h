#pragma once
#include "BaseScene.h"
#include "main.h"

class GameClear :public BaseScene
{
private:
	int	m_texture_gameclear;
	int	m_texture_gameclear2;
	
	bool  select_flag = false;
	int gameover = 0;
	int g_AnimePtn = 0;
	int g_AnimePtn2 = 0;
	int g_AnimeCounter = 0;
	int frame = 0;
	int BGMNo;
public:
	GameClear(SceneChanger* changer) :BaseScene(changer) {};//構築時に自動的に呼ばれる
	~GameClear() {};//破棄時に自動的に呼ばれる
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	int GetStage(void) { return gameover; }
	bool CheckClear(void) { return true; }
};
