/*****************************************
 * Block�w�b�_						     *
 *�^�[�U���u���b�N�̃N���X               *
 *										 *
 *         Auther:		�~���x			 *
 *         SpecialThanks:�A�x�m�����X    *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"




class BLOCK :public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int use;
	bool hit_bullet = false;
	int state;
	BULLET* pBullet = nullptr;
	
public:
	
	BLOCK(class Game* game,D3DXVECTOR2 pos);//�����I�ɌĂ΂��
	~BLOCK() {};//�����I�ɌĂ΂��
	void Init(void)   ;
	void Uninit(void) ;
	void Update(void) ;
	void Draw(void) ;
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	enum Block_state
	{
		BLOCK_STATE_AIR,//�󒆃u���b�N(���z��SPD�}��)
		BLOCK_STATE_GRAND,//�n��̃u���b�N
		BLOCK_STATE_GIMIC,//�M�~�b�N�̃u���b�N(�M�~�b�N�̏����͕ʂōs��)
		BLOCK_STATE_NONE//���ɂ�������Ȃ�����
	};
	void Hitbullet(bool state) { hit_bullet = state; }
	bool GetHit(void) { return hit_bullet; }
};
