/*****************************************
 * Title�w�b�_							 *
 *�^�C�g���V�[���̊Ǘ����s���N���X       *
 *										 *
 *         Auther:	�E�`���}			 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseScene.h"
#include "main.h"

#define MOVE_SPEED 5.0f
#define MOVE_UP   0.6f
class Title :public BaseScene
{
private:
	int  m_texture_bg;		//�Ŕw�ʔw�i
	int  m_texture_new;	    //�j���[�Q�[��
	int  m_texture_load;	//���[�h
	int  m_texture_op;		//�I�v�V����
	int  m_texture_exit;	//�I��
	int  m_texture_title;    //�^�C�g��  �{���ǉ�

	int  m_BGMNo;
	int  m_SENo;
	int  m_SENo2;

	D3DXVECTOR2 pos_new;
	D3DXVECTOR2 pos_load;
	D3DXVECTOR2 pos_op;
	D3DXVECTOR2 pos_exit;
	D3DXVECTOR2 pos_title;//�{���ǉ�

	D3DXVECTOR2 pos_new_first;
	D3DXVECTOR2 pos_load_first;
	D3DXVECTOR2 pos_op_first;
	D3DXVECTOR2 pos_exit_first;


	D3DXVECTOR2 vel_new;
	D3DXVECTOR2 vel_load;
	D3DXVECTOR2 vel_op;
	D3DXVECTOR2 vel_exit;

	int select_menu = 2;
	float frame = 0;
	bool exit = false;

	bool flag_new = false;
	bool flag_load = false;
	bool flag_op = false;
	bool flag_exit = false;

	class Option* op = nullptr;

	enum {
		MODE_EXIT,
		MODE_LOAD,
		MODE_NEW,
		MODE_OP,		
		

		MODE_MAX,

	};

public:
	Title(SceneChanger* changer) :BaseScene(changer) {};//�\�z���Ɏ����I�ɌĂ΂��
	~Title() {};//�j�����Ɏ����I�ɌĂ΂��
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��

	void ResetPosNew(void) { if (pos_new.y < pos_new_first.y)pos_new.y += MOVE_SPEED; };
	void ResetPosLoad(void) { if (pos_load.y < pos_load_first.y)pos_load.y += MOVE_SPEED; };
	void ResetPosOp(void) { if (pos_op.y < pos_op_first.y)pos_op.y += MOVE_SPEED; };
	void ResetPosExit(void) { if (pos_exit.y < pos_exit_first.y)pos_exit.y += MOVE_SPEED; };

	bool ExitCheck(void) { return exit; }
};

