#include "BossArm.h"
#include "texture.h"
#include "sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "CharacterManager.h"
#include "collision.h"
#include "BossArm.h"
#include "Boss.h"
#include "Player.h"
#include "Fieldcollision.h"
#include <cstdlib>

#include <iostream>
#include <random>

void BOSSARM::Init()
{
	arm_boss.pos_init = Chara.pos;
	Chara.vel = D3DXVECTOR2(0.0f, 0.0f);
	if (arm_boss.dir_id == LEFT)
		Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/Arm_L.png");
	else
		Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/Arm_R.png");

	frame = 300;

	count = 0;

	p_boss = game()->GetCm()->GetBoss();
	pPlayer = game()->GetCm()->GetPlayer();
	map[0][0] = game()->map()->GetMap();
}

void BOSSARM::Uninit()
{
}

void BOSSARM::Update()
{
	Chara.pos += Chara.vel;
	
	
}

void BOSSARM::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	DrawSprite(Chara.m_TextureNo,
		basePos.x + Chara.pos.x,
		basePos.y + Chara.pos.y,
		200, 100,
		0.0f, 0.0f,
		1.0f,
		1.0f);
}

void BOSSARM::SwingArm(void)
{


	if (swing == true) {
		if(count == 0)
		Chara.vel.x = -10.0f;
		if (abs(Chara.pos.x - arm_boss.pos_init.x) >= 200.0f) {
			Chara.vel.x = 0.0f;

			if (arm_boss.move_down) {
				SwingDown();

			}
			else if (arm_boss.move_up) {
				SwingUp();
			}
			
		}
		if (count >= 3) {
			arm_boss.move_down = false;
			arm_boss.move_up = false;
			ReturnArm();
			
		}
		
		
	}


	


	
}

void BOSSARM::SwingUp(void)
{
	

	Chara.vel.y = -10.0f;

	if (Chara.pos.y - arm_boss.pos_init.y <= -100.0f) {
		Chara.vel.y = 0.0f;

		arm_boss.move_down = true;
		arm_boss.move_up = false;
		count++;
	}
		
	
}

void BOSSARM::SwingDown(void)
{
	Chara.vel.y = 10.0f;

	if (Chara.pos.y - arm_boss.pos_init.y >= 200.0f) {
		Chara.vel.y = 0.0f;

		arm_boss.move_down = false;
		arm_boss.move_up = true;
	}
}

void BOSSARM::StartSwing(void)
{
	swing = true; 
	if (arm_boss.dir_id == LEFT) {
		arm_boss.move_down = true;
		arm_boss.move_up = false;
	}
	else {
		arm_boss.move_down = false;
		arm_boss.move_up = true;
	}
}

void BOSSARM::ReturnArm(void)
{
		pos_back = arm_boss.pos_init - Chara.pos;
		D3DXVec2Normalize(&pos_back, &pos_back);
		Chara.pos += (pos_back * 10.0f);
		
		D3DXVECTOR2 vDist;
		vDist = Chara.pos - arm_boss.pos_init;

		float len = D3DXVec2Length(&vDist);

		

		//if (abs(Chara.pos.x - arm_boss.pos_init.x) <= 100.0f) {
		//	Chara.pos.x = arm_boss.pos_init.x;

		//}
		//if (abs(Chara.pos.y - arm_boss.pos_init.y) <= 10.0f) {
		//	Chara.pos.y = arm_boss.pos_init.y;

		//}
		if (len < 10.0f) {
			Chara.pos = arm_boss.pos_init;
			p_boss->SetFrame(420);
			swing = false;
			count = 0;
		}
}

void BOSSARM::RocketArm(void)
{
	if (arm_boss.rocket_move) {
		MoveRocket();
	}
	else if (arm_boss.rocket_back) {

		if(arm_boss.move_pattern == 0)
			ReturnRocketArm();
		else if(arm_boss.move_pattern == 1)
			ReturnRocketArm2();//ひきずる方
		/*else{
			std::random_device rd;
			std::uniform_int_distribution<> dist(0, 1);

			arm_boss.move_pattern = dist(rd);
			
		}*/
	}
}

void BOSSARM::MoveRocket(void)
{
	if (abs(arm_boss.pos_init.x - Chara.pos.x <= 500.0f)) {
		
		Chara.vel.x += -0.5f;
	}
	else
	{
		Chara.vel.x = 0.0f;
		
		//ここでエフェクトを切る
		
		if (hit_field == true) {
			Chara.vel.y = 0.0f;
			frame--;
			if (frame <= 0.0f) {
				arm_boss.rocket_move = false;
				arm_boss.rocket_back = true;
			}

		}
		else {
			Chara.vel.y += 0.5f;
		}
	
		
	}
}

void BOSSARM::StartRocket(void)
{
	rocket = true;
	arm_boss.rocket_move = true;
	arm_boss.rocket_back = false;

	hit_field = false;

	Chara.pos.y = pPlayer->GetPlayerPos().y - 50.0f;
	frame = 300.0f;
	//arm_boss.move_pattern = 1;
}

void BOSSARM::ReturnRocketArm(void)
{
	pos_back = arm_boss.pos_init - Chara.pos;
	D3DXVec2Normalize(&pos_back, &pos_back);
	Chara.pos += (pos_back * 10.0f);

	D3DXVECTOR2 vDist;
	vDist = Chara.pos - arm_boss.pos_init;

	float len = D3DXVec2Length(&vDist);


	if (len < 10.0f) {
		Chara.pos = arm_boss.pos_init;
		p_boss->SetFrame(300);
		rocket = false;
		arm_boss.rocket_move = false;
		arm_boss.rocket_back = false;
		arm_boss.move_pattern = 1;
		
	}
}

void BOSSARM::ReturnRocketArm2(void)
{
	pos_back = arm_boss.pos_init - Chara.pos;
	D3DXVec2Normalize(&pos_back, &pos_back);
	Chara.pos.x += (pos_back.x * 10.0f);

	D3DXVECTOR2 vDist;
	vDist = Chara.pos - arm_boss.pos_init;

	float len = D3DXVec2Length(&vDist);


	if (len <= 170.0f) {
		Chara.pos = arm_boss.pos_init;
		p_boss->SetFrame(300);
		rocket = false;
		arm_boss.rocket_move = false;
		arm_boss.rocket_back = false;
		arm_boss.move_pattern = 0;
	}
}
