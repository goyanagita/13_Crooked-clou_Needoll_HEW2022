/*****************************************
 * Enemy_Beeヘッダ					     *
 *敵の蜂のクラス			             *
 *										 *
 *         Author:ミヤベ				 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Character.h"
#define S_ENEMY_SIZE_X 128
#define S_ENEMY_SIZE_Y 128

class Enemy_Bee:public Character
{
private:

	enum ENEMY_STATE {
		ENEMY_STATE_REST,
		ENEMY_STATE_SHOOT,
		ENEMY_STATE_RETURN,
	};

	struct DATA {
		int AnimPtn;
		int muki;
		int AnimCounter;
		float MoveRangeX;//移動範囲(横)
		float MoveRangeY;//移動範囲(縦)
		float survFlag = 1;
		float		speed;	//移動スピード
		D3DXVECTOR2 dir;	//移動方向
		D3DXVECTOR2 startPos;//発生位置
		int DeathPtn;
		bool hit_bullet = 0;

		//宮部追加
		int m_TextureNo2;

	};

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

	DATA f_bee;
	class BEEBULLET* ebb;

public:
	Enemy_Bee(class Game* game, D3DXVECTOR2 pos) :Character(game) { Chara.pos = pos; };
	~Enemy_Bee() {};
	void Init();
	void Uninit() {};
	void Update();
	void Draw();
	void MoveBee();
	void ReverseEbX(void) { Chara.vel.x *= -1; }
	D3DXVECTOR2 GetEnBeePos() { return Chara.pos; }


	bool GetSave() { return f_bee.survFlag; }
	void SetSave(bool flag) { f_bee.survFlag = flag; }
	void SetHitBullet(bool hit) { f_bee.hit_bullet = hit; }
	bool GetHitBullet(void) { return f_bee.hit_bullet; }
	D3DXVECTOR2 GetVel(void) { return Chara.vel; }
	D3DXVECTOR2 GetPos(void) { return Chara.pos; }


};

