#pragma once
/*****************************************
 * ItomakiRecovery�w�b�_				 *
 *���̉񕜂̊Ǘ����s���N���X             *
 *�u���b�N�I�Ȃ̂�������                 *
 �����蔻����ɓ���Ǝ����񕜂���d�l    *
 *         Auther:			�E�`���}	 *
 *         Date  :						 *
 *****************************************/

#include "GameObject.h"
#include "main.h"

class ItomakiRecovery :public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	float rot = 1.0f;

	int save_flag;
	int use;

	int state;
	

public:

	ItomakiRecovery(class Game* game,D3DXVECTOR2 pos);
	~ItomakiRecovery() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	
	
	//enum Block_state
	//{
	//	BLOCK_STATE_AIR,//�󒆃u���b�N(���z��SPD�}��)
	//	BLOCK_STATE_GRAND,//�n��̃u���b�N
	//	BLOCK_STATE_GIMIC,//�M�~�b�N�̃u���b�N(�M�~�b�N�̏����͕ʂōs��)
	//	BLOCK_STATE_NONE//���ɂ�������Ȃ�����
	//};
};