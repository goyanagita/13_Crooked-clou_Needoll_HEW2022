/*****************************************
 * Player�w�b�_							 *
 *�v���C���[�̊Ǘ����s���N���X           *
 *										 *
 *         Auther:�E�`���}               *      		 
 *�@�@�@�@�@�@�@�@(�^�[�U���̂݃~���x)   *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Character.h"
#include "camera.h"
#include "input.h"
#include "inputx.h"
#include "ObjectManager.h"

#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�

#define DIVIDE_X 8	//���̕�����
#define DIVIDE_Y 24	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

#define PLAYER_DISP_X (SCREEN_WIDTH/2)	//�v���C���[�̕\�����WX
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)	//�v���C���[�̕\�����WY

#define ROT_SPEED 0.0005f

#define MAX_THREAD 100.0f


class Player :public Character
{
public:
	enum Player_state
	{
		BLOCK_STING,
		PLAY_AIR,
		PLAY_NUM,
	};

private:
	struct DATA {
		D3DXVECTOR2 pos_old;
		float  pos_old_jump;	//�W�����v�O�̍��W
		float height;
		float		jumpPower;//�W�����v��
		float pendulum;

		int			animePtn;
		int			animeCounter;

		bool        touch;//�����蔻��Ɏg��
		bool        tarzan;
		bool		flag_throw;//�j�����t���O

		D3DXVECTOR2   pdir;//�v���C���[�̈ړ�����
		float ang;//�u���b�N�ƃv���C���[�̍ŏ��p�x
		float m_ang;      //ang���������
		float s_angle;

		Player_state state;
		float		gravity;//�d��
		int pattern;
		float		gravity_fall;
		int rightAnimId = 0;//�E�����̎�
		int leftAnimId = 1;//�������̎�
		int jumpFlag = 0;//�W�����v�t���O�E�E�E1�̎��W�����v���Ă���
		float nowWx = 0;//�H�����ݖh�~�p(���݂̈ʒu���W)
		bool survFlag = 0;//���S���� 1�Ȃ玀�S���`����~�߂�
		float rot = 0.0f;
		float speed_rot = 0.0f;

		bool walk = false;

		bool hit_enemy = false;

		bool hit_anime = false;
		//float thread_cap;
		//float thread_use;
		int attack_cnt = 0;
		int damage_cnt = 0;

    //=================================
    //1/25���R�ǉ�
    //=================================
		float thread_dash_cnt = 0;
		bool  thread_dash = false;
		float walk_sound_frame = 60.0f;

	};
	DATA player;

	D3DXVECTOR2		dir_bullet = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 dif_ladder = D3DXVECTOR2(0.0f, 0.0f);

	class BULLET* bl;
	class Attack* at;
	class ThreadGauge* tg;
	class CharacterManager* cm;//�L�����N�^�[�}�l�[�W���[�|�C���^
	class Ladder* ladder[MAX_LADDER];
	CAMERA_2D* camera;

	//�{���ǉ�
	class ObjectManager* om;//�I�u�W�F�N�g�}�l�[�W���[�|�C���^
	int	m_SENo;		//SE���ʎq
	int m_SENo2;


public:
	Player(class Game* game, D3DXVECTOR2 pos) :Character(game) { Chara.pos = pos; }
	~Player() {};
	void Init();//������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	void MovePlayer();
	void Anime(void);
	void AttackSting();
	void ThrowThread();
	void Sew(void);
	void Life(int life) { Chara.hp += life; }
	void HitBullet();


	D3DXVECTOR2 GetPlayerPos() { return Chara.pos; }

	float GetSpeed() { return Chara.speed; }
	float GetJumpPow() { return player.jumpPower; }
	bool GetPlayerSurv(void) { return player.survFlag; }
	void SetOldJump(float pos_jump) { player.pos_old_jump = pos_jump; }
	bool GetJumpFlag() { return player.jumpFlag; }
	bool GetTarzanFlag(void) { return player.tarzan; }
	void SetJumpFlag(float jump) { player.jumpFlag = jump; }
	void SetTarzan(bool tarzan) { player.tarzan = tarzan; }
	void SetJumpPow(float pow) { player.jumpPower = pow; }
	void SetPosX(float pos) { Chara.pos.x += pos; }
	void SetHit(bool hit) { player.hit_enemy = hit; }
	void JumpSet(void);

	void TarzanExit(void);


	bool GetPatternR(void);
	bool GetPatternL(void);

	Player_state ChanegeState(Player_state state) { return player.state = state; }
};

/*

1,�j�̉�]�̂�����

2,�j����]������ۂ̓����蔻��

	�j�̃|�W�V�����ɉ�]�p�x�������Ă����������蔻��ɉ�]�p�x��������
	or
	�v���C���[�͓����蔻��𓊂���
	���̓����蔻��ɒǏ]����`�Őj��`��

3,�j�̌��ɂ��Ă��������ǂ����邩

	�j�̉ߋ����W�ɕ`�悳���Ă���ɉ�]�p�x�𑫂��Ă����B


*/