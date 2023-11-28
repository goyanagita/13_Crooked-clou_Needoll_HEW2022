/*****************************************
 *DownBook�w�b�_                         *
 *(�R���ƃw�b�_��������Ă����̂ŕύX)   *
 *                              �~���x   * 
 *�{�̃N���X							 *
 *										 *
 *         Auther:�R��		�@�@�@		 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"




class DOWNBOOK :public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	

	bool flag;
	int use;
	float rot;
	float cnt;

	class BULLET* bl = nullptr;

public:

	DOWNBOOK(class Game* game, D3DXVECTOR2 pos);
	~DOWNBOOK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
};