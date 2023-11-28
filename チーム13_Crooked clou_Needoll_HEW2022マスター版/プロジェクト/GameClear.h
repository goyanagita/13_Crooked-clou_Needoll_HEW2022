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
	GameClear(SceneChanger* changer) :BaseScene(changer) {};//�\�z���Ɏ����I�ɌĂ΂��
	~GameClear() {};//�j�����Ɏ����I�ɌĂ΂��
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	int GetStage(void) { return gameover; }
	bool CheckClear(void) { return true; }
};
