/*****************************************
 * Pause�w�b�_							 *
 *�|�[�Y��ʂ̊Ǘ����s���N���X			 *
 *										 *
 *         Auther:	�E�`���}		     *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"

class Pause
{
private:
	int m_textrue_no;
	D3DXVECTOR2 m_pos;


	int select_menu = 0;

	bool exit_menu = false;
public:
	
	Pause() {};
	~Pause() {};
	void Init()	;//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw()	;//�`�揈��

	bool GetExitMenu(void) { return exit_menu; }
};

