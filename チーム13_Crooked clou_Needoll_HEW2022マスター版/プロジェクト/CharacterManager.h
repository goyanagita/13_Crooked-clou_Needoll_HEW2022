/*****************************************
 * CharacterManagerヘッダ			     *
 *キャラクターの管理を行うクラス         *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Character.h"
#include "Player.h"
#include "GameObject.h"

#define ENEMY_FIELD_MAX 20
#define ENEMY_SPIDER_MAX (2)			//フィールド　最大数

 //宮部追加------------------------
#define BIRD_MAX 100
#define BEE_MAX 100
#define E_BULLET 100
#define B_BULLET 100


class CharacterManager:public GameObject
{
private:

	struct DATA {
		int numPlayer = 0;//プレイヤー
		int numPlayerBullet = 0;//針
		int numEnemy_Field = 0;//地上敵
		//int numEnemy_Air = 0;//空中敵
		//int numEnemy_AirBullet = 0;//空中敵の弾
		
	};

	int Total = 0;
	int total_enemy_f = 0;
	int total_enemy_w = 0;//とり//宮部追加
	int total_enemy_s = 0;//はち
	int total_spider = 0;
	float hit_frame = 0;
	class Character** Characters = nullptr;
	class Player* player = nullptr;
	class BOSS* boss = nullptr;
	Character* Enemy = nullptr;
	int m_SENo;


protected:
	class Enemy_Field* f_Enemy[ENEMY_FIELD_MAX];
	class Spider* spider[ENEMY_SPIDER_MAX];
	class Enemy_Bird* f_Bird[BIRD_MAX];	//宮部追加
	class Enemy_Bee* f_Bee[BEE_MAX];
public:
	CharacterManager(class Game* game);
	~CharacterManager();
	void create(int ID,D3DXVECTOR2 pos);
	void appear(char charaId, float wx, float wy, float vx = 0, float vy = 0) {};
	void Init();
	void Uninit();
	void Update() ;
	void Draw();
	int GetEnemyfTotal(void){ return total_enemy_f; }
	class Player* GetPlayer();
	class Enemy_Field* GetEnemyField(int i);
	class BOSS* GetBoss();
	void SubTotal(void) { total_enemy_f--; }
	void HitCharacter(void);

	//宮部追加
	class Enemy_Bird* GetBird(int i);
	class Enemy_Bee* GetBee(int i);
	int GetEnemywTotal(void) { return total_enemy_w; }
	int GetEnemysTotal(void) { return total_enemy_s; }
};

