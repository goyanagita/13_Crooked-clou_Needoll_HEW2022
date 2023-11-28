/*****************************************
 * ObjectManagerヘッダ					 *
 * オブジェクトの管理をするクラス        *
 *										 *
 *         Auther:	ウチヤマ			 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Block.h"
#include "GameObject.h"

#define MAX_SPOOL 100
#define MAX_BOOK	100
#define MAX_BOOK_P	100
#define MAX_BOOK_D	100//宮部追加
#define MAX_BLOCK 100
#define MAX_LADDER 100
#define MAX_THREAD_HEAL 100
#define BRIDGE_POAL 20//ポール一本で1つ(20で10組の橋ができる)
#define MAX_HP_HEAL 100
#define MAX_BREAK 100


class ObjectManager:public GameObject {
private:
	class BLOCK* block[MAX_BLOCK];
	class Ladder* ladder[MAX_LADDER];
	class ITOMAKI* spool[MAX_SPOOL];
	class AUTOBOOK* book_a[MAX_BOOK];
	class PULLBOOK*  book_pull[MAX_BOOK_P];
	class Goal* goal = nullptr;
	class ItomakiRecovery* thread_heal[MAX_THREAD_HEAL];
	class DOWNBOOK* book_d[MAX_BOOK_D];

	class Bridge* bridge[BRIDGE_POAL];//宮部追加
	class HPRecovery* hp_heal[MAX_HP_HEAL];
	class ItomakiBreak* itomaki_break[MAX_BREAK];



	int total_block = 0;
	int total_ladder = 0;
	int total_spool = 0;
	int total_book	 = 0;
	int total_book_p = 0;

	int total_book_d = 0;//宮部追加
	int total_heal = 0;
	int total_poal = 0;
	int total_hp = 0;
	int total_break = 0;

public:
	ObjectManager(class Game* game);
	~ObjectManager() {};
	void create(int ID, D3DXVECTOR2 pos);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	class BLOCK* GetBlock(int i) { return block[i]; }
	class Ladder* GetLadder(int i) { return ladder[i]; }
	class PULLBOOK* GetpBook(int i) { return book_pull[i]; }
	class Bridge* GetBridge(int i);//宮部追加
	class ItomakiBreak* Getitomakibreak(int i) { return itomaki_break[i]; }

	int GetTotalBlock(void) { return total_block; }
	int GetTotalSpool(void) { return total_spool; }
	int GetTotalBook(void) { return total_book; }
	int GetTotalBookP(void) { return total_book_p; }
	int GetTotalBookD(void) { return total_book_d; }
	int GetTotalLadder(void) { return total_ladder; }
	int GetTotalThreadHeal(void) { return total_heal; }
	int  GetAnimPtn(int i);
	int GetPoalTotal(void) { return total_poal; }
	int GetTotalHPHeal(void) { return total_hp; }
	int GetTotalBreak(void) { return total_break; }


};