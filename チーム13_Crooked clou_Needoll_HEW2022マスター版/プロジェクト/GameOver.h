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
	GameOver(SceneChanger* changer) :BaseScene(changer){};//�\�z���Ɏ����I�ɌĂ΂��
	~GameOver() {};//�j�����Ɏ����I�ɌĂ΂��
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	int GetStage(void) { return gameover; }
	bool CheckClear(void) { return false; }
};
