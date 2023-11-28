/*****************************************
 * Spiderヘッダ			     　　　　　　*
 *敵の蜘蛛のクラス(Coming Soon)　　　　　*
 *										 *
 *         Auther:	ミヤベ　　　　　	 *
 *         Date  :						 *
 *****************************************/
#pragma once	//多重定義の禁止

#include "main.h"
#include "renderer.h"
#include "Character.h"

//**************************************************************
//マクロ定義
//**************************************************************
#define ENEMY_MAX			(2)			//フィールド　最大数
#define ENEMY_SIZE			(64.0f)		//フィールド　サイズ



//**************************************************************
//構造体
//**************************************************************
class Enemy :public Character
{
protected:
	enum Enemy_state {
		STS_NULL = 0,
		STS_SPAWN,
		STS_NORMAL,
	};

	struct DATA
	{
		bool		useFg;
		int			status;	
	};
	
	DATA enemy;


public:
	Enemy(class Game* game) :Character(game) {}
	~Enemy() {};

	virtual void Init() = 0;//初期化
	virtual void Uninit() = 0;//終了処理
	virtual void Update() = 0;//更新処理
	virtual void Draw() = 0;//描画処理
	bool Collision(D3DXVECTOR2 pos);


	//ゲッター
	D3DXVECTOR2	GetPos() { return Chara.pos; }
	bool		GetUse() { return enemy.useFg; }
	int			GetStatus() { return enemy.status; }

};

class Spider : public Enemy {
private:
	struct DATA
	{
		float		posStart;
		float		posSpawn;
	};
	const float m_AnimTbl[5] =
	{
		0.0f,
		0.25f,
		0.5f,
		0.75f,
		0.0f
	};
	DATA spider;
	//D3DXVECTOR2 pos;
public:
	Spider(class Game* game, D3DXVECTOR2 pos);
	
	void Init()override;//初期化
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	//void Init(void);//初期化
	//void Uninit(void);//終了処理
	//void Update(void);//更新処理
	//void Draw(void);//描画処理

	//更新処理
	void Update_Null(D3DXVECTOR2 PlayerPos);
	void Update_Spawn(D3DXVECTOR2 PlayerPos);
	void Update_Back(D3DXVECTOR2 PlayerPos);


	//ステータス変更関数
	void ChangeStatus(Enemy_state state) { enemy.status = state; }
};
