#pragma once
/*****************************************
 * BOSSArm�w�b�_					     *
 * BOSSArm�̊Ǘ����s���N���X	         *
 *										 *
 *         Auther:		�E�`���}		 *
 *         Date  :						 *
 *****************************************/
#include"Character.h"

#include "Map.h"

class BOSSARM :public Character
{
private:
	struct DATA {
		D3DXVECTOR2 pos_init;
		int AnimPtn;
		int muki;
		int AnimCounter = 0;
		int jumpFlag = 0;//�W�����v�t���O�E�E�E1�̎��W�����v���Ă���
		float nowWx = 0;//�H�����ݖh�~�p(���݂̈ʒu���W)
		bool survFlag = 0;//���S���� 0�Ȃ玀�S���`����~�߂�
		bool hit_bullet = false;

		//int m_wave;
		bool move_up = false;
		bool move_down = false;

		bool rocket_move = false;
		bool rocket_back = false;
		int dir_id;
		int	move_pattern = 1;
	};
	bool swing = false;

	bool rocket = false;
	class BULLET* bl;
	class BOSS* p_boss;
	class Player* pPlayer = nullptr;
	DATA arm_boss;
	MAP::DATA map[MAX_YMAP][MAX_XMAP];

	D3DXVECTOR2 pos_back;
	float frame;
	int count;

	bool hit_field = false;

public:

	BOSSARM(class Game* game, D3DXVECTOR2 pos, int dir) :Character(game) { Chara.pos = pos; arm_boss.dir_id = dir; };
	~BOSSARM() {};
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	void ResetPos(void) { Chara.pos = arm_boss.pos_init; Chara.vel = D3DXVECTOR2(0.0f, 0.0f); }

	//�r��U�艺�낷�s��
	void SwingArm(void);

	void SwingUp(void);
	void SwingDown(void);

	void StartSwing(void);
	void ReturnArm(void);

	bool GetSwing(void) { return swing; }

	//���P�b�g�p���`������s��

	void RocketArm(void);

	void MoveRocket(void);

	void StartRocket(void);
	void ReturnRocketArm(void);

	void ReturnRocketArm2(void);
	bool GetRocket(void) { return rocket; }

	enum DIR {
		RIGHT,
		LEFT,
	};

	D3DXVECTOR2 GetPos(void) { return Chara.pos; }
	void SetHitField(bool state) { hit_field = state; }

	//bool GetSave() { return f_enemy.survFlag; }
	//bool GetHitBullet(void) { return f_enemy.hit_bullet; }
	//D3DXVECTOR2 GetVel(void) { return Chara.vel; }
	//void SetSave(bool flag) { f_enemy.survFlag = flag; }
	//void SetHitBullet(bool hit) { f_enemy.hit_bullet = hit; }
};
