/*****************************************
 *PullBook�w�b�_                         *
 *(�R���ƃw�b�_��������Ă����̂ŕύX)   *
 *                              �~���x   *
 *�����Ɠ|���{�̃N���X((Coming Soon)	 *
 *										 *
 *         Author:�R��		�@�@�@		 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"




class PULLBOOK :public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	float rot;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int fool_flag;
	int pull_flag;
	int use;

	int state;
	BULLET* pBullet = nullptr;
	class CharacterManager* cm;
	#pragma once

public:

	PULLBOOK(class Game* game, D3DXVECTOR2 pos);
	~PULLBOOK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	enum Block_state
	{
		BLOCK_STATE_AIR,//�󒆃u���b�N(���z��SPD�}��)
		BLOCK_STATE_GRAND,//�n��̃u���b�N
		BLOCK_STATE_GIMIC,//�M�~�b�N�̃u���b�N(�M�~�b�N�̏����͕ʂōs��)
		BLOCK_STATE_NONE//���ɂ�������Ȃ�����
	};
};
