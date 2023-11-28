#include "Boss.h"
#include "texture.h"
#include "sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "CharacterManager.h"
#include "collision.h"
#include "BossArm.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy_Field.h"

#include <iostream>
#include <random>

#define DIVIDE_X 4
#define DIVIDE_Y 1
#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)



BOSS::BOSS(class Game * game, D3DXVECTOR2 pos, class BOSSARM * p_r, class BOSSARM * p_l) :Character(game)
{
	Chara.pos = pos;
	arm_r = p_r;
	arm_l = p_l;
}

void BOSS::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/kuma01-sheet.png");
	Chara.hp = 10;
	boss.m_wave = WAVE3;
	boss.fream_atack = 360.0f;

	bl = game()->GetBullet();
	pl = game()->GetCm()->GetPlayer();
	arm_r->Init();
	arm_l->Init();
	for (int i = 0; i < 10; i++)
		boss_enemy[i] = nullptr;

	boss.use = true;
}

void BOSS::Uninit()
{
	for (int i = 10; i >= 0; i--)
	{
		if (boss_enemy[i] != nullptr) {
			boss_enemy[i]->Uninit();
			delete boss_enemy[i];
			boss_enemy[i] = nullptr;
			
		}
	}
	if(arm_r != nullptr)
	{
		delete arm_r;
		arm_r = nullptr;
	}
	if(arm_l != nullptr)
	{
		delete arm_l;
		arm_l != nullptr;
	}
}

void BOSS::Update()
{
	if (boss.use == true) {
		switch (boss.m_wave) {
		case WAVE1:
			MoveWave1();
			break;
		case WAVE2:
			MoveWave2();
			break;
		case WAVE3:
			MoveWave3();
			break;

		}
		boss.fream_atack--;
		arm_r->Update();
		arm_l->Update();

		if (boss.m_wave < WAVE3 && Chara.hp <= 0) {
			Chara.hp = 10;
			boss.m_wave++;
			arm_r->ResetPos();
			arm_l->ResetPos();
			boss.fream_atack = 300;

			for (int i = 10; i >= 0; i--)
			{
				if (boss_enemy[i] != nullptr) {
					boss_enemy[i]->Uninit();
					delete boss_enemy[i];
					boss_enemy[i] = nullptr;

				}
			}
		}
		else if (boss.m_wave >= WAVE3 && Chara.hp <= 0)
		{
			boss.use = false;
		}

		if (boss.use == true) {
			if (HitCheckBox(bl->GetPos(), 64.0f, 64.0f,Chara.pos, BOSS_SIZE_X, BOSS_SIZE_Y)) {
				
				bl->SetHitBoss(true);
				boss.hit_bullet_boss = true;
				
			}
		}
	}
	
}

void BOSS::Draw()
{
	if (boss.use == true) {
		D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

		arm_l->Draw();
		arm_r->Draw();

		DrawSprite(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			BOSS_SIZE_X, BOSS_SIZE_Y,
			0.0f, 0.0f,
			PATTERN_WIDTH,
			PATTERN_HEIGHT);

		for (int i = 0; i < 10; i++) {
			if (boss_enemy[i] != nullptr) {
				boss_enemy[i]->Draw();
			}
		}
	}
	else return;

}

void BOSS::MoveEnemy()
{
}

void BOSS::MoveWave1(void)
{
	if (boss.fream_atack <= 0.0f && arm_l->GetSwing() == false) {
		//確率で腕振り下ろし、敵生成
	/*	std::random_device rd;
		std::uniform_int_distribution<> dist(0, 1);
		
		boss.move_pattern = dist(rd);*/
		switch (boss.move_pattern)
		{
		case 0://腕を振る
			arm_l->StartSwing();
			arm_r->StartSwing();
			boss.move_pattern = 1;
			break;
		case 1:
			//敵を作る
			for (int i = 0; i < 10; i++) {
				if (boss_enemy[i] == nullptr) {
					boss_enemy[i] = new Enemy_Field(game(),D3DXVECTOR2(Chara.pos.x + (40 * i), Chara.pos.y + (BOSS_SIZE_Y / 2)));
					boss_enemy[i]->Init();
				}
			}
			boss.move_pattern = 0;
			boss.fream_atack = 420;
			break;
		}
	}
	

	if (arm_l->GetSwing() == true)
		arm_l->SwingArm();
	if (arm_r->GetSwing() == true)
		arm_r->SwingArm();

	

	for (int i = 0; i < 10; i++) {
		if (boss_enemy[i] != nullptr) {
			boss_enemy[i]->Update();

			if (abs((Chara.pos.x - boss_enemy[i]->GetPos().x)) >= 900) {
				boss_enemy[i]->Uninit();
				delete boss_enemy[i];
				boss_enemy[i] = nullptr;
				
			}
		}
	}
	
}

void BOSS::MoveWave2(void)
{
	if (boss.fream_atack <= 0.0f && arm_l->GetRocket() == false) {
		//確率でロケットパンチ、綿ブロック生成
		std::random_device rd;
		std::uniform_int_distribution<> dist(0, 1);

		boss.move_pattern = dist(rd);
		switch (boss.move_pattern)
		{
		case 0://ロケットパンチ
			arm_l->StartRocket();
			
			break;
		case 1://綿生成
			break;
		}
	}


	if (arm_l->GetRocket() == true)
		arm_l->RocketArm();
}

void BOSS::StartJump(void)
{

	boss.jumpPower = 12.0f;
	boss.gravity = 0.33f;
	boss.pos_old_jump = Chara.pos.y;
	boss.jump_purpose = pl->GetPlayerPos().x - Chara.pos.x;
	boss.frame_jump = 0.0f;
	boss.hit_field = false;
	boss.jumpFlag = true;
	
}



void BOSS::Jump(void)
{
	Chara.pos.y -= boss.jumpPower;
	Chara.pos.x += (boss.jump_purpose * 0.01f);
	boss.jumpPower -= boss.gravity;
	
	if (boss.hit_field == true) {

		UninitJump();
	}

}

void BOSS::UninitJump(void)
{
	Chara.pos.y = boss.pos_old_jump;
	boss.jumpFlag = false;
	boss.fream_atack = 300;
}

void BOSS::MoveWave3(void)
{
	if (boss.fream_atack <= 0.0f && boss.jumpFlag == false) {
		//確率でジャンプ
		StartJump();
	}

	if (boss.jumpFlag == true) {
		Jump();
	}
	if (boss.jumpFlag == false)
		boss.frame_jump++;
	if (boss.frame_jump <= 60) {
		if (HitCheckBox(pl->GetPlayerPos(), 64.0f, 64.0f, D3DXVECTOR2(Chara.pos.x - (BOSS_SIZE_X / 2), Chara.pos.y /*- (BOSS_SIZE_Y / 2)*/), 150.0f, 400.0f)) {
			pl->SetPosX(-3.0f);
		}
		if (HitCheckBox(pl->GetPlayerPos(), 64.0f, 64.0f, D3DXVECTOR2(Chara.pos.x + (BOSS_SIZE_X / 2), Chara.pos.y ), 150.0f, 400.0f)) {
			pl->SetPosX(3.0f);
		}
	}
}

/*
腕の振り下ろしは腕の画像を個別に貰ってそのままイラスト差し替え

ウェーブの切り替えは敵を縫い付けるアニメーションを適宜その部位の座標で表示

ロケットパンチは腕の後ろにエフェクトを追尾させる→これは腕が横に飛んでいる間だけ描画

ジャンプは腕を振っているチップをもらう予定


*/