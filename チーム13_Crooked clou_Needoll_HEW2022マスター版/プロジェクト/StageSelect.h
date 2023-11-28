/*****************************************
 * StageSelect�w�b�_					 *
 *�X�e�[�W�̊Ǘ����s���N���X             *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseScene.h"
#include "main.h"

class StageSelect :public BaseScene
{
private:
	int m_texture_selectbg;
	int  m_texture_1st;//�X�e�[�W1
	int  m_texture_2nd;//�X�e�[�W2
	int  m_texture_3rd;//�X�e�[�W3
	int  m_texture_4th;//�X�e�[�W4
	int  m_texture_5th;//�X�e�[�W5
	int m_texture_player;

	int m_SENo;

	D3DXVECTOR2 pos_slctbg;
	D3DXVECTOR2 pos_1st;
	D3DXVECTOR2 pos_2nd;
	D3DXVECTOR2 pos_3rd;
	D3DXVECTOR2 pos_4th;
	D3DXVECTOR2 pos_5th;
	D3DXVECTOR2 pos_player;


	bool  flag_first = false;//�X�e�[�W�N���A������true�ɂ���
	bool  flag_second = false;//�X�e�[�W�N���A������true�ɂ���
	bool  flag_third = false;//�X�e�[�W�N���A������true�ɂ���
	bool  flag_fourth = false;//�X�e�[�W�N���A������true�ɂ���
	bool  flag_fifth = false;//�X�e�[�W�N���A������true�ɂ���

	int stg_select = 0;
	int CC = 0; //����`�F�b�N�@�X�e�[�W�N���A���Ƃ�+1����

	int	stage_now;
	bool exit = false;

	bool goal_check = false;

	float frame = 0; 
	enum {
		STG_1st,//0
		STG_2nd,//1
		STG_3rd,//2
		STG_4th,//3
		STG_5th,//4

		STG_MAX,
	};

public:
	StageSelect(SceneChanger* changer) :BaseScene(changer) {};//�\�z���Ɏ����I�ɌĂ΂��
	~StageSelect() {};//�j�����Ɏ����I�ɌĂ΂��
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	int GetStage(void) { return stg_select; }
	void SetClear(void) { goal_check = true; }
	void SetStageInfo(int stage) 
	{ 
		stg_select = stage; 
		CC = stage; 
		stage_now = stage;
		switch (stage) {
		case 0:
			pos_player = D3DXVECTOR2(pos_1st.x, pos_1st.y - 90.0f);;
			break;
		case 1:
			pos_player = pos_2nd;
			pos_player.x += 50;
			flag_first = true;
			break;
		case 2:
			pos_player = pos_3rd;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			break;
		case 3:
			pos_player = pos_4th;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			flag_third = true;
			break;
		case 4:
			pos_player = pos_5th;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			flag_third = true;
			flag_fourth = true;
			break;

		}
	}
};
