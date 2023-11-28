/*****************************************
 * SceneManager�w�b�_					 *
 *�V�[���̊Ǘ����s���N���X			     *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
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
	BaseScene* m_Scene = nullptr;//�V�[���̊Ǘ��ϐ�
	eScene m_NextScene ;//���̃V�[���̊Ǘ��ϐ�
	bool game_exit = false;
	bool exit_check = false;
	int stage_info = 0;
	int stage_next = 0;
	bool stage_select = false;
	bool game = false;
	bool stage_clear = false;
public:
	SceneManager() ;//�\�z���Ɏ����I�ɌĂ΂��
	void Init() ;//������
	void Uninit() ;//�I������
	void Upadate() ;//�X�V����
	void Draw() ;//�`�揈��

	void ChangeScene(eScene NextScene);
	void SetErrorFlag(void) { game_exit = true; }
	bool GetExitFlag(void) { return exit_check; }
	bool GetErrorFlag(void) { return game_exit; }
	//void StageInfo(int stage) { stage_info = stage; }

};

