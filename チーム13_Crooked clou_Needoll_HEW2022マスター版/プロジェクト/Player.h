/*****************************************
 * Playerヘッダ							 *
 *プレイヤーの管理を行うクラス           *
 *										 *
 *         Auther:ウチヤマ               *      		 
 *　　　　　　　　(ターザンのみミヤベ)   *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Character.h"
#include "camera.h"
#include "input.h"
#include "inputx.h"
#include "ObjectManager.h"

#define NUM_VERTEX 4	//必要な頂点の数

#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 24	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

#define PLAYER_DISP_X (SCREEN_WIDTH/2)	//プレイヤーの表示座標X
#define PLAYER_DISP_Y (SCREEN_HEIGHT/2)	//プレイヤーの表示座標Y

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
		float  pos_old_jump;	//ジャンプ前の座標
		float height;
		float		jumpPower;//ジャンプ力
		float pendulum;

		int			animePtn;
		int			animeCounter;

		bool        touch;//当たり判定に使う
		bool        tarzan;
		bool		flag_throw;//針投げフラグ

		D3DXVECTOR2   pdir;//プレイヤーの移動方向
		float ang;//ブロックとプレイヤーの最小角度
		float m_ang;      //ang動かすやつ
		float s_angle;

		Player_state state;
		float		gravity;//重力
		int pattern;
		float		gravity_fall;
		int rightAnimId = 0;//右向きの時
		int leftAnimId = 1;//左向きの時
		int jumpFlag = 0;//ジャンプフラグ・・・1の時ジャンプしている
		float nowWx = 0;//食い込み防止用(現在の位置座標)
		bool survFlag = 0;//死亡判定 1なら死亡→描画を止める
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
    //1/25内山追加
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
	class CharacterManager* cm;//キャラクターマネージャーポインタ
	class Ladder* ladder[MAX_LADDER];
	CAMERA_2D* camera;

	//宮部追加
	class ObjectManager* om;//オブジェクトマネージャーポインタ
	int	m_SENo;		//SE識別子
	int m_SENo2;


public:
	Player(class Game* game, D3DXVECTOR2 pos) :Character(game) { Chara.pos = pos; }
	~Player() {};
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
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

1,針の回転のさせ方

2,針を回転させる際の当たり判定

	針のポジションに回転角度を持っておく→当たり判定に回転角度をかける
	or
	プレイヤーは当たり判定を投げる
	その当たり判定に追従する形で針を描画

3,針の後ろについていく糸をどうするか

	針の過去座標に描画させてそれに回転角度を足していく。


*/