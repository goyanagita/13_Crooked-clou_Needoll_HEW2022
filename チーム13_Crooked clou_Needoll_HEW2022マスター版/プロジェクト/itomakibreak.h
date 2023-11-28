/*****************************************
 * itomakibreak�w�b�_				     *
 *�j�󂳂�鎅�����̃N���X               *
 *�������������ăv���C���[�͒ʉ߂ł��Ȃ� *
 *���j�𓖂Ă邱�Ƃŉ���d�l           *  
 *         Auther:	���c			 �@�@*
 *         Date  :						 *
 *****************************************/
#pragma once


#include "GameObject.h"
#include "main.h"
#define ITOMAKIBREAK_NUM		(10)		// �G�t�F�N�g��Max��

 // �o���b�g�\����
struct EXPLOSION
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:�g���Ă���  false:���g�p
	bool					bloken; // �j��A�j���[�V�������t���O
	D3DXVECTOR3				pos;	// �o���b�g�̍��W
	D3DXVECTOR3				dir;	// �o���b�g�̈ړ�����
	float					speed;	// �o���b�g�̈ړ��X�s�[�h
	float					frame;	// �t���[����
	int						anmIndex;//�A�j���[�V�����p�^�[��
	int						anmWait;//�p�^�[���̕\���E�G�C�g
};



class ItomakiBreak :public GameObject {
private:
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq
	int m_TextureNo2 = 0;//�e�N�X�`���̎��ʎq
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	float rot = 0.0f;

	int save_flag;
	int use;
	int						anmIndex;//�A�j���[�V�����p�^�[��
	int						anmWait;//�p�^�[���̕\���E�G�C�g
	int state;
	int SENo;

	float	frame;	// �t���[����
	int AnimPtn = 0;
	int AnimCounter;
	bool broken = false;
	

public:

	ItomakiBreak(class Game* game, D3DXVECTOR2 pos);
	~ItomakiBreak() {};
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
private:
	struct DATA {


		int			animePtn;
		int			animeCounter;
		int muki;
	};
	DATA itomakibreak;

};


