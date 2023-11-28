#include "ObjectManager.h"
#include "Game.h"
#include "Ladder.h"
#include "itomaki.h"
#include "AutoBook.h"
#include "PullBook.h"
#include "ItomakiRecovery.h"
#include "goal.h"
#include "DownBook.h"
#include "Bridge.h"
#include "HPRecovery.h"
#include "itomakibreak.h"

//===================================================================
// コンストラクタ
//===================================================================
ObjectManager::ObjectManager(class Game * game):GameObject(game)
{

}
//===================================================================
// オブジェクトの生成処理(引数:キャラID ,座標)
//===================================================================
void ObjectManager::create(int ID, D3DXVECTOR2 pos)
{

	/*IDが
		0なら...ターザンブロック生成
		1なら...梯子ブロック生成
		2なら...糸巻き生成
		3なら...本生成
		4なら...動く本生成
		5なら...ゴール
		6なら...橋
		7なら...糸回復アイテム
	*/

	switch (ID)
	{
	case 0:
		if(total_block < MAX_BLOCK)
		block[total_block++] = new BLOCK(game(),pos);
		break;
	case 1:
		if(total_ladder < MAX_LADDER)
		ladder[total_ladder++] = new Ladder(game(), pos);
		break;
	case 2:
		if(total_spool < MAX_SPOOL)
		spool[total_spool++] = new ITOMAKI(game(),pos);
		break;
	case 3:
		if (total_book < MAX_BOOK)
			book_a[total_book++] = new AUTOBOOK(game(), pos);
		break;
	case 4:
		if (total_book_p < MAX_BOOK_P)
			book_pull[total_book_p++] = new PULLBOOK(game(), pos);
		break;
	case 5:
		goal = new Goal(game(), pos);
		break;

		//宮部追加
	case 6:
		if (total_poal < BRIDGE_POAL)
			bridge[total_poal++] = new Bridge(game(), pos);
		break;
	case 7:
		if (total_heal < MAX_THREAD_HEAL)
			thread_heal[total_heal++] = new ItomakiRecovery(game(), pos);
		break;
	case 8:
		if (total_book_d < MAX_BOOK_D)
			book_d[total_book_d++] = new DOWNBOOK(game(), pos);
		break;
	case 9:
		if (total_hp < MAX_HP_HEAL)
			hp_heal[total_hp++] = new HPRecovery(game(), pos);
		break;
	case 10:
		if (total_break < MAX_BREAK)
			itomaki_break[total_break++] = new ItomakiBreak(game(), pos);
		break;
	}
}

//===================================================================
// 初期化処理
//===================================================================
void ObjectManager::Init()
{
	//インスタンスの初期化
	
	for (int i = 0; i < total_block; i++) {
		if (block[i] != nullptr) {
			block[i]->Init();
		}
	}
	for (int i = 0; i < total_ladder; i++) {
		if (ladder[i] != nullptr)
			ladder[i]->Init();
	}
	
	for (int i = 0; i < total_spool; i++) {
		if (spool[i] != nullptr) {
			spool[i]->Init();
		}
	}
	for (int i = 0; i < total_book; i++) {
		if (book_a[i] != nullptr) {
			book_a[i]->Init();
		}
	}
	for (int i = 0; i < total_book_p; i++) {
		if (book_pull[i] != nullptr) {
			book_pull[i]->Init();
		}
	}
	if (goal != nullptr) {
		goal->Init();
	}
	for (int i = 0; i < total_heal; i++) {
		if (thread_heal[i] != nullptr) {
			thread_heal[i]->Init();
		}
	}

	//宮部追加
	for (int i = 0; i < total_book_d; i++) {
		if (book_d[i] != nullptr) {
			book_d[i]->Init();
		}
	}
	for (int i = 0; i < total_poal; i++) {
		if (bridge[i] != nullptr)
			bridge[i]->Init();
	}
	for (int i = 0; i < total_hp; i++) {
		if (hp_heal[i] != nullptr) {
			hp_heal[i]->Init();
		}
	}
	for (int i = 0; i < total_break; i++) {
		if (itomaki_break[i] != nullptr) {
			itomaki_break[i]->Init();
		}
	}
}


//===================================================================
// 終了処理
//===================================================================
void ObjectManager::Uninit()
{	
	for (int i = total_heal- 1; i >= 0; i--)
	{
		if (thread_heal[i] != nullptr) {
			thread_heal[i]->Uninit();
			delete thread_heal[i];
			thread_heal[i] = nullptr;
		}
	}

	if (goal != nullptr) {
		goal->Uninit();
		delete goal;
		goal = nullptr;
	}
	for (int i = total_book_p - 1; i >= 0; i--)
	{
		if (book_pull[i] != nullptr) {
			book_pull[i]->Uninit();
			delete book_pull[i];
			book_pull[i] = nullptr;
		}
	}
	for (int i = total_book - 1; i >= 0; i--)
	{
		if (book_a[i] != nullptr) {
			book_a[i]->Uninit();
			delete book_a[i];
			book_a[i] = nullptr;
		}
	}
	for (int i = total_spool - 1; i >= 0; i--)
	{
		if (spool[i] != nullptr) {
			spool[i]->Uninit();
			delete spool[i];
			spool[i] = nullptr;
		}
	}
	//インスタンスの解放
	for (int i = total_ladder - 1; i >= 0; i--)
	{
		if (ladder[i] != nullptr) {
			ladder[i]->Uninit();
			delete ladder[i];
			ladder[i] = nullptr;
		}
	}
	for (int i = total_block - 1; i >= 0; i--)
	{
		if (block[i] != nullptr) {
			block[i]->Uninit();
			delete block[i];
			block[i] = nullptr;
		}
	}

	//宮部追加
	for (int i = total_book_d - 1; i >= 0; i--)
	{
		if (book_d[i] != nullptr) {
			book_d[i]->Uninit();
			delete book_d[i];
			book_d[i] = nullptr;
		}
	}
	for (int i = 0; i <= total_poal; i++)
	{
		if (bridge[i] != nullptr)
		{
			bridge[i]->Uninit();
			delete bridge[i];
			bridge[i] = nullptr;
		}
	}
	for (int i = 0; i < total_hp; i++)
	{
		if (hp_heal[i] != nullptr)
		{
			hp_heal[i]->Uninit();
			delete hp_heal[i];
			hp_heal[i] = nullptr;
		}
	}
	for (int i = 0; i < total_break; i++)
	{
		if (itomaki_break[i] != nullptr)
		{
			itomaki_break[i]->Uninit();
			delete itomaki_break[i];
			itomaki_break[i] = nullptr;
		}
	}
}

//===================================================================
// 更新処理
//===================================================================
void ObjectManager::Update()
{
	//インスタンスの更新
	for (int i = 0; i < total_block; i++) {
		if (block[i] != nullptr) {
			block[i]->Update();
		}
	}
	
	for (int i = 0; i < total_ladder; i++) {
		if (ladder[i] != nullptr) {
			ladder[i]->Update();
		}
	}
	for (int i = 0; i < total_spool; i++) {
		if (spool[i] != nullptr) {
			spool[i]->Update();
		}
	}
	for (int i = 0; i < total_book; i++) {
		if (book_a[i] != nullptr) {
			book_a[i]->Update();
		}
	}
	for (int i = 0; i < total_book_p; i++) {
		if (book_pull[i] != nullptr) {
			book_pull[i]->Update();
		}
	}
	if (goal != nullptr) {
		goal->Update();
	}
	for (int i = 0; i < total_heal; i++) {
		if (thread_heal[i] != nullptr) {
			thread_heal[i]->Update();
		}
	}

	//宮部追加
	for (int i = 0; i < total_book_d; i++) {
		if (book_d[i] != nullptr) {
			book_d[i]->Update();
		}
	}
	for (int i = 0; i < total_poal; i++) {
		if (bridge != nullptr)
			bridge[i]->Update();
	}
	for (int i = 0; i < total_hp; i++) {
		if (hp_heal[i] != nullptr)
			hp_heal[i]->Update();
	}
	for (int i = 0; i < total_break; i++) {
		if (itomaki_break[i] != nullptr)
			itomaki_break[i]->Update();
	}
}

//===================================================================
// 描画処理
//===================================================================
void ObjectManager::Draw()
{

	//インスタンスの描画
	for (int i = 0; i < total_block; i++) {
		if (block[i] != nullptr) {
			block[i]->Draw();
		}
	}

	for (int i = 0; i < total_ladder; i++) {
		if (ladder[i] != nullptr) {
			ladder[i]->Draw();
		}
	}
	for (int i = 0; i < total_spool; i++) {
		if (spool[i] != nullptr) {
			spool[i]->Draw();
		}
	}
	for (int i = 0; i < total_book; i++) {
		if (book_a[i] != nullptr) {
			book_a[i]->Draw();
		}
	}
	for (int i = 0; i < total_book_p; i++) {
		if (book_pull[i] != nullptr) {
			book_pull[i]->Draw();
		}
	}
	if (goal != nullptr) {
		goal->Draw();
	}
	for (int i = 0; i < total_heal; i++) {
		if (thread_heal[i] != nullptr) {
			thread_heal[i]->Draw();
		}
	}

	//宮部追加
	for (int i = 0; i < total_book_d; i++) {
		if (book_d[i] != nullptr) {
			book_d[i]->Draw();
		}
	}
	for (int i = 0; i < total_poal; i++)
	{
		if (bridge[i] != nullptr)
			bridge[i]->Draw();
	}
	for (int i = 0; i < total_hp; i++)
	{
		if (hp_heal[i] != nullptr)
			hp_heal[i]->Draw();
	}
	for (int i = 0; i < total_break; i++)
	{
		if (itomaki_break[i] != nullptr)
			itomaki_break[i]->Draw();
	}
}


//宮部追加
Bridge* ObjectManager::GetBridge(int i)
{
	return bridge[i];
}

int ObjectManager::GetAnimPtn(int i)
{
	return bridge[i]->GetAnim();
}
