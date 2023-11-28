#pragma once
/*****************************************
 * BOSSヘッダ							 *
 * BOSSの管理を行うクラス	             *
 *										 *
 *         Auther:						 *
 *         Date  :						 *
 *****************************************/

#include"Character.h"


#define BOSS_SIZE_X (32.0f*8)
#define BOSS_SIZE_Y (32.0f*12)

class BOSS :public Character
{
private:
	struct DATA {
		int AnimPtn;
		int muki;
		int AnimCounter = 0;
		int jumpFlag = 0;//ジャンプフラグ・・・1の時ジャンプしている
		float nowWx = 0;//食い込み防止用(現在の位置座標)
		bool survFlag = 0;//死亡判定 0なら死亡→描画を止める
		bool hit_bullet = false;

		int m_wave;
		float fream_atack;

		int move_pattern = 0;

		bool jump = false;
		float jumpPower;//ジャンプ力
		float gravity;
		float jump_purpose;
		float  pos_old_jump;
		float frame_jump;
		bool hit_field = false;
		bool hit_bullet_boss = false;

		int use = false; 

	};
	/*const float m_AnimTbl[5] =
	{
		0.0f,
		0.25f,
		0.5f,
		0.75f,
		0.0f
	};

	const float m_MukiTbl[2] =
	{
		0.0f,
		1.0f,
	};*/
	class BULLET* bl;
	class Player* pl;
	class BOSSARM* arm_r = nullptr;
	class BOSSARM* arm_l = nullptr;
	class Enemy_Field* boss_enemy[10];

	DATA boss;

	enum BOSS_WAVE {
		WAVE1,
		WAVE2,
		WAVE3,

		WAVE_NUM,
	};

public:

	BOSS(class Game * game, D3DXVECTOR2 pos, class BOSSARM* p_r, class BOSSARM* p_l);
	~BOSS() {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void MoveEnemy();
	void MoveWave1(void);
	void MoveWave2(void);
	void StartJump(void);
	void Jump(void);
	void UninitJump(void);
	void MoveWave3(void);

	void SetFrame(float time) { boss.fream_atack = time; }

	class BOSSARM* GetArmR(void){return arm_r;};
	class BOSSARM* GetArmL(void){return arm_l;};

	D3DXVECTOR2 GetPos(void) { return Chara.pos; }
	void SetHitField(bool state) { boss.hit_field = state; }
	void SetHitBullet(bool hit) { boss.hit_bullet_boss = hit; }
	int GetWave(void) { return boss.m_wave; }
	void SetDamage(int damage) { Chara.hp -= damage; }
	int GetUse(void) { return boss.use; }
	bool GetJump(void) { return boss.jump; }
	//bool GetSave() { return f_enemy.survFlag; }
	//bool GetHitBullet(void) { return f_enemy.hit_bullet; }
	//D3DXVECTOR2 GetVel(void) { return Chara.vel; }
	//void SetSave(bool flag) { f_enemy.survFlag = flag; }
	//void SetHitBullet(bool hit) { f_enemy.hit_bullet = hit; }
};

