#pragma once
#include "BaseScene.h"
#include "main.h"

class GameOver :public BaseScene
{
private:
	int	m_texture_gameover;
	int	m_texture_gameover2;
	int	m_texture_retry;
	int	m_texture_retry2;
	int m_texture_select;
	int m_texture_select2;

	D3DXVECTOR2 pos_gameover;
	D3DXVECTOR2 pos_retry;
	D3DXVECTOR2 pos_retry2;
	D3DXVECTOR2 pos_select;
	D3DXVECTOR2 pos_select2;

	bool  select_flag = false;
	int gameover = 0;
	int g_AnimePtn = 0;
	int g_AnimePtn2 = 0;
	int g_AnimeCounter = 0;
	int frame = 0;
	int BGMNo;
	int m_SENo2;
public:
	GameOver(SceneChanger* changer) :BaseScene(changer){};//構築時に自動的に呼ばれる
	~GameOver() {};//破棄時に自動的に呼ばれる
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	int GetStage(void) { return gameover; }
	bool CheckClear(void) { return false; }
};
