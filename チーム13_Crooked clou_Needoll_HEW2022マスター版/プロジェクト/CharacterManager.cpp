#include "CharacterManager.h"
#include "Game.h"

#include "Character.h"
#include "Enemy_Field.h"
#include "collision.h"
#include "Boss.h"
#include "BossArm.h"
#include "Enemey_Spider.h"
#include "Enemy_Bird.h"
#include "Enemy_Bee.h"
#include "Bridge.h"
#include "EnemyBullet.h"
#include "BeeBullet.h"

#include "sound.h"

#include "inputx.h"

//=============================================================================
// コンストラクタ処理
//=============================================================================
CharacterManager::CharacterManager(class Game* game):GameObject(game)
{

}

//=============================================================================
// キャラクターの生成処理(引数:キャラID ,座標)
//=============================================================================
void CharacterManager::create(int ID,D3DXVECTOR2 pos)
{
	/*IDが
		0なら...プレイヤー生成
		1なら...地上敵生成
		2なら...蜘蛛生成
		3なら...ボス生成
	*/


	switch(ID) {
		case 0:
			player = new Player(game(), pos);
			break;
		case 1:
			if(total_enemy_f < ENEMY_FIELD_MAX)
				f_Enemy[total_enemy_f++] = new Enemy_Field(game(),pos);
			break;
		case 2:
			if (total_spider < ENEMY_SPIDER_MAX)
				spider[total_spider++] = new Spider(game(),pos);
			break;
		case 3:
			boss = new BOSS(game(), pos,
				new BOSSARM(game(), pos,BOSSARM::DIR::RIGHT),
				new BOSSARM(game(), pos, BOSSARM::DIR::LEFT)
			);
			break;
			//宮部追加
		case 4:
			if (total_enemy_w < BIRD_MAX)
				f_Bird[total_enemy_w++] = new Enemy_Bird(game(), pos);
			break;
		case 5:
			if (total_enemy_s < BEE_MAX)
				f_Bee[total_enemy_s++] = new Enemy_Bee(game(), pos);
			break;
	}
	
	 
}

//=============================================================================
// デストラクタ
//=============================================================================
CharacterManager::~CharacterManager() {

	
}

//=============================================================================
// 初期化処理
//=============================================================================
void CharacterManager::Init()
{   
	m_SENo = LoadSound((char*)"data/SE/ダメージ.wav");

	if(player != nullptr)
		player->Init();	
	
	for (int i = 0; i < total_enemy_f; i++)
	{
		if (f_Enemy[i] != nullptr)
			f_Enemy[i]->Init();

	}
	for (int i = 0; i < total_spider; i++)
	{
		if (spider[i] != nullptr)
			spider[i]->Init();

	}
	if (boss != nullptr)
		boss->Init();
	hit_frame = 0;
	
	//宮部追加
	for (int i = 0; i < total_enemy_w; i++)
	{
		if (f_Bird[i] != nullptr)
			f_Bird[i]->Init();
	}
	for (int i = 0; i < total_enemy_s; i++)
	{
		if (f_Bee[i] != nullptr)
			f_Bee[i]->Init();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CharacterManager::Uninit() {

	//インスタンスの生成した逆順から解放
	if (boss != nullptr) {
		boss->Uninit();
		delete boss;
		boss = nullptr;
	}

	for (int i = total_spider - 1; i >= 0; i--)
	{
		if (spider[i] != nullptr) {
			spider[i]->Uninit();
			delete spider[i];
			spider[i] = nullptr;
		}
	}
	for (int i = total_enemy_f - 1; i >= 0; i--)
	{
		if (f_Enemy[i] != nullptr) {
			f_Enemy[i]->Uninit();
			delete f_Enemy[i];
			f_Enemy[i] = nullptr;
			
		}
	}
	if (player != nullptr) {
		player->Uninit();
		delete player;
		player = nullptr;
	}
	//宮部追加------------------------------------------
	for (int i = total_enemy_w - 1; i >= 0; i--)
	{
		if (f_Bird[i] != nullptr) {
			f_Bird[i]->Uninit();
			delete f_Bird[i];
			f_Bird[i] = nullptr;
		}
	}
	for (int i = total_enemy_s - 1; i >= 0; i--)
	{
		if (f_Bee[i] != nullptr)
		{
			f_Bee[i]->Uninit();
			delete f_Bee[i];
			f_Bee[i] = nullptr;
		}
	}

	StopSoundAll();

}

//=============================================================================
// 更新処理
//=============================================================================
void CharacterManager::Update() {
	if(player->GetPlayerSurv() != false)
		player->Update();
	for (int i = 0; i < total_enemy_f; i++)
	{
		if (f_Enemy[i] != nullptr)
			f_Enemy[i]->Update();

	}
	for (int i = 0; i < total_spider; i++)
	{
		if (spider[i] != nullptr)
			spider[i]->Update();

	}
	if (game()->map()->GetBossFlag() == true) {
		D3DXVECTOR2 vDist;
		vDist = player->Chara.pos - boss->Chara.pos;
		float len = D3DXVec2Length(&vDist);
		if (boss != nullptr && len < 700.0f)
			boss->Update();
	}

	//宮部追加---------------------------
	for (int i = 0; i < total_enemy_w; i++)
	{
		f_Bird[i]->Update();
	}
	for (int i = 0; i < total_enemy_s; i++)
	{
		f_Bee[i]->Update();
	}

	hit_frame++;
	if (hit_frame >= 240) {//当たったら4秒間無敵
		HitCharacter();
		X_StopVibration(0);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CharacterManager::Draw() {

	for (int i = 0; i < total_enemy_f ;i++)
	{
		if (f_Enemy[i] != nullptr)
			f_Enemy[i]->Draw();

	}
	for (int i = 0; i < total_spider; i++)
	{
		if (spider[i] != nullptr)
			spider[i]->Draw();

	}

	//宮部追加
	for (int i = 0; i < total_enemy_w; i++)
	{
		f_Bird[i]->Draw();
	}

	for (int i = 0; i < total_enemy_s; i++)
	{
		f_Bee[i]->Draw();
	}

	if (boss != nullptr)
		boss->Draw();

	if (player->GetPlayerSurv())
	player->Draw();
}

//=============================================================================
// プレイヤーのゲッター
//=============================================================================
Player * CharacterManager::GetPlayer()
{
	return player;
}

//===================================================================
// 地上敵のゲッター(引数: 何番目か →　呼ぶ側でループさせる)
//===================================================================
Enemy_Field * CharacterManager::GetEnemyField(int i)
{
	return f_Enemy[i];
}

BOSS * CharacterManager::GetBoss()
{
	return boss;
}

void CharacterManager::HitCharacter(void)
{
	ENEMYBULLET* eb = nullptr;
	BEEBULLET* bb = nullptr;

	eb = game()->GetEnemyBullet();
	bb = game()->GetBeeBullet();

	for (int i = 0; i < total_enemy_f; i++) {
		if (f_Enemy[i]->GetSave() != true)
			continue;
		if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X/1.5, PLAYER_SIZE_Y/1.5, f_Enemy[i]->GetPos(), F_ENEMY_SIZE_X, F_ENEMY_SIZE_Y)) {
			player->Life(-1);
			X_SetRightVibration(0, 120);//0127
			player->SetHit(true);
			hit_frame = 0;
			PlaySound(m_SENo, 0);
			if (player->GetTarzanFlag()) {
				player->TarzanExit();
			}

		}

	}
	for (int i = 0; i < total_enemy_w; i++) {
		if (f_Bird[i]->GetSave() != true)
			continue;
		if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, f_Bird[i]->GetPos(), W_ENEMY_SIZE_X, W_ENEMY_SIZE_Y)) {
			player->Life(-1);
			X_SetVibration(0, 120);
			player->SetHit(true);
			hit_frame = 0;
			PlaySound(m_SENo, 0);
			if (player->GetTarzanFlag()) {
				player->TarzanExit();
			}

		}

	}
	for (int i = 0; i < total_enemy_s; i++) {
		if (f_Bee[i]->GetSave() != true)
			continue;
		if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, f_Bee[i]->GetPos(), S_ENEMY_SIZE_X, S_ENEMY_SIZE_Y)) {
			player->Life(-1);
			X_SetVibration(0, 120);
			player->SetHit(true);
			hit_frame = 0;
			PlaySound(m_SENo, 0);
			if (player->GetTarzanFlag()) {
				player->TarzanExit();
			}
		}
	}
	for (int i = 0; i < total_spider; i++) {
		if (spider[i]->GetUse() != true)
			continue;
		if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, spider[i]->GetPos(), ENEMY_SIZE, ENEMY_SIZE)) {
			player->Life(-1);
			X_SetVibration(0, 120);
			player->SetHit(true);
			hit_frame = 0;		
			PlaySound(m_SENo, 0);
			if (player->GetTarzanFlag()) {
				player->TarzanExit();
			}
		}

	}

	if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, eb->GetEbPos(), 32, 32)) {
		player->Life(-1);
		X_SetVibration(0, 120);
		player->SetHit(true);
		hit_frame = 0;
		PlaySound(m_SENo, 0);
	}

	if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, bb->GetBbPos(), 32, 32)) {
		player->Life(-1);
		X_SetVibration(0, 120);
		player->SetHit(true);
		hit_frame = 0;
		PlaySound(m_SENo, 0);

	}

	if (boss != nullptr) {
		if (!boss->GetJump()) {
			if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, boss->GetPos(), BOSS_SIZE_X, BOSS_SIZE_Y)) {
				player->Life(-1);
				X_SetVibration(0, 120);
				player->SetHit(true);
				hit_frame = 0;
				PlaySound(m_SENo, 0);
			}
		}
		else {
			if (HitCheckBox(player->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, boss->GetPos(), BOSS_SIZE_X, BOSS_SIZE_Y)) {
				player->Life(-3);
				X_SetVibration(0, 120);
				player->SetHit(true);
				hit_frame = 0;
				PlaySound(m_SENo, 0);

			}
		}
	}
}

//宮部追加
//===================================================================
// 鳥のゲッター(引数: 何番目か →　呼ぶ側でループさせる)
//===================================================================
Enemy_Bird* CharacterManager::GetBird(int i)
{
	return f_Bird[i];
}

//===================================================================
// 蜂のゲッター(引数: 何番目か →　呼ぶ側でループさせる)
//===================================================================
Enemy_Bee* CharacterManager::GetBee(int i)
{
	return f_Bee[i];
}
