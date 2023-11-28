/*****************************************
 * Enemy_Fieldヘッダ					 *
 *地上敵のクラス			             *
 *										 *
 *         Auther:	ミヤベ				 *
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
		int jumpFlag = 0;//ジャンプフラグ・・・1の時ジャンプしている
		float nowWx = 0;//食い込み防止用(現在の位置座標)
		bool survFlag = 0;//死亡判定 0なら死亡→描画を止める
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
	D3DXVECTOR2 GetEnFieldPos() { return Chara.pos; }//宮部追加
	void ReverseEfX(void) { Chara.vel.x *= -1; }

};

