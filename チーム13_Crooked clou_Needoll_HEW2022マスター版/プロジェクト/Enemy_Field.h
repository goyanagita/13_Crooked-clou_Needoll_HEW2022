/*****************************************
 * Enemy_Field�w�b�_					 *
 *�n��G�̃N���X			             *
 *										 *
 *         Auther:	�~���x				 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include"Character.h"
#define F_ENEMY_SIZE_X 128
#define F_ENEMY_SIZE_Y 128

class Enemy_Field :public Character
{
private:
	struct DATA {
		int AnimPtn;
		int DeathPtn;
		int muki;
		int AnimCounter = 0;
		int jumpFlag = 0;//�W�����v�t���O�E�E�E1�̎��W�����v���Ă���
		float nowWx = 0;//�H�����ݖh�~�p(���݂̈ʒu���W)
		bool survFlag = 0;//���S���� 0�Ȃ玀�S���`����~�߂�
		bool hit_bullet = false;
		int m_TextureNo2;


	};
	const float m_AnimTbl[8] =
	{
		0.0f,
		0.125f,
		0.25f,
		0.375f,
		0.5f,
		0.625f,
		0.75f,
		0.875f,
	};

	const float m_DeathTbl[10] =
	{
		0.0f,
		0.1f,
		0.2f,
		0.3f,
		0.4f,
		0.5f,
		0.6f,
		0.7f,
		0.8f,
		0.9f,
	};

	const float m_MukiTbl[2] =
	{
		0.0f,
		1.0f,
	};

	DATA f_enemy;

public:
	
	Enemy_Field(class Game* game, D3DXVECTOR2 pos) :Character(game) { Chara.pos = pos; };
	~Enemy_Field() {};
	void Init();
	void Uninit() {};
	void Update();
	void Draw();
	void MoveEnemy();
	bool GetSave() { return f_enemy.survFlag; }
	bool GetHitBullet(void) { return f_enemy.hit_bullet; }
	D3DXVECTOR2 GetVel(void){ return Chara.vel; }
	void SetSave(bool flag) { f_enemy.survFlag = flag; }
	void SetHitBullet(bool hit) { f_enemy.hit_bullet = hit; }
	D3DXVECTOR2 GetPos(void) { return Chara.pos; }
	D3DXVECTOR2 GetEnFieldPos() { return Chara.pos; }//�{���ǉ�
	void ReverseEfX(void) { Chara.vel.x *= -1; }

};

