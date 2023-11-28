/*****************************************
 * Enemy_Birdヘッダ					     *
 *鳥のクラス			           　　  *
 *										 *
 *         Author:ミヤベ				 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include"Character.h"
#define W_ENEMY_SIZE_X 128
#define W_ENEMY_SIZE_Y 128

class Enemy_Bird :public Character
{
private:
	struct DATA {
		int AnimPtn;
		int muki;
		int AnimCounter;
		float survFlag;
		float MoveRangeB_Y;//鳥の移動範囲
		int m_TextureNo2;
		bool hit_bullet = 0;
		int DeathPtn;
	};

	DATA f_bird;

	const float m_MukiTbl[2] =
	{
		0.0f,
		1.0f,
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
	
	class ENEMYBULLET* ebl;

public:
	Enemy_Bird(class Game* game, D3DXVECTOR2 pos) :Character(game) { Chara.pos = pos; };
	~Enemy_Bird() {};
	void Init();
	void Uninit() {};
	void Update();
	void Draw();
	void MoveBird();

	bool GetSave() { return f_bird.survFlag; }
	void SetSave(bool flag) { f_bird.survFlag = flag; }
	void SetHitBullet(bool hit) { f_bird.hit_bullet = hit; }
	bool GetHitBullet(void) { return f_bird.hit_bullet; }
	D3DXVECTOR2 GetVel(void) { return Chara.vel; }
	D3DXVECTOR2 GetPos(void) { return Chara.pos; }



};



