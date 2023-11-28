/*********************************************
 * Ladder�w�b�_								 *
 *�j���h���������֏㏸����u���b�N�̃N���X *
 *										     *
 *         Auther:�E�`���}					 *
 *         Date  :12/12						 *
 *********************************************/
#pragma once

#include "main.h"
#include "GameObject.h"

class Goal: public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;


	int save_flag;
	int use;

	int state;

	bool flag_goal = false;
	class Player* pl = nullptr;
	
public:
	Goal(class Game* game, D3DXVECTOR2 pos);
	~Goal() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	

};