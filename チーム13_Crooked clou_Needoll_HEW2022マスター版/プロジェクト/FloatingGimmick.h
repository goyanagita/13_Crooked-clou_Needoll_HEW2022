/*****************************************
 * FloatingGimmick�w�b�_			�@�@ *
 *���V�M�~�b�N�̃N���X        �@�@�@ �@�@*
 *										 *
 *         Auther:		�R��		 �@�@*
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"


#define MAX_GIMMICK 8		//���V�M�~�b�N�̌�
#define RIGHT_END 1500.0f	//���V�M�~�b�N�G���A�̉E�[

	struct GIMMICK
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 vel;
		float rot;
		D3DXVECTOR2 first_pos;

		int save_flag;
		int fool_flag;
		int use;

		int state;
	};
	static GIMMICK g_Gimmick[MAX_GIMMICK];


class FLGIMMICK :public GameObject {
private:

	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	BULLET* pBullet = nullptr;
	class CharacterManager* cm;
public:

	FLGIMMICK(class Game* game,D3DXVECTOR2 pos);
	~FLGIMMICK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	enum Block_state
	{
		BLOCK_STATE_AIR,//�󒆃u���b�N(���z��SPD�}��)
		BLOCK_STATE_GRAND,//�n��̃u���b�N
		BLOCK_STATE_GIMIC,//�M�~�b�N�̃u���b�N(�M�~�b�N�̏����͕ʂōs��)
		BLOCK_STATE_NONE//���ɂ�������Ȃ�����
	};
};