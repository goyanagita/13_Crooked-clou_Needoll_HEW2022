/*****************************************
 * Option�w�b�_							 *
 *�I�v�V������ʂ̊Ǘ����s���N���X		 *
 *										 *
 *         Auther:		�E�`���}		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"

class Option
{
private:
	int m_textrue_no;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_vel;
	D3DXVECTOR2 m_pos_purpose;
	D3DXVECTOR2 m_pos_init;

	int select_option = 0;

	bool exit_option = false;
	bool finish = false;
public:

	Option() {};
	~Option() {};
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��

	bool GetExitOption(void) { return exit_option; }
	
	bool GetFinish(void) { return finish; }
};


