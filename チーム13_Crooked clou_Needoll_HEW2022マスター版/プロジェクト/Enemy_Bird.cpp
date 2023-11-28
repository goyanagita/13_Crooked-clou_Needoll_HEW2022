#include "Enemy_Bird.h"
#include "GameObject.h"
#include "Game.h"
#include "Character.h"
#include "CharacterManager.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "Count.h"
#include "EnemyBullet.h"
#include "Player.h"

#define DIVIDE_X 8
#define DIVIDE_Y 4
#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static float g_MukiTbl[4]
{
	0.0f,
	0.25f,
	0.5f,
	0.75f,
};

void Enemy_Bird::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/カラス4.png");
	f_bird.m_TextureNo2 = LoadTexture((char*)"data/TEXTURE/deathcrow.png");
	Chara.vel = D3DXVECTOR2(0.0f, 1.8f);
	f_bird.AnimPtn =  0;
	f_bird.survFlag = true;//0なら死亡
	f_bird.muki = 0;
	ebl = game()->GetEnemyBullet();
	Chara.hp = 3;
}

void Enemy_Bird::Update()
{
	int gc = GetCount();

	if (f_bird.survFlag == true)
	{
		MoveBird();
		if (f_bird.AnimCounter > 40) {
			f_bird.AnimPtn++;
			if (f_bird.AnimPtn >= 8)
				f_bird.AnimPtn = 0;
			f_bird.AnimCounter = 0;
		}

		if (gc % 13 == 0)
		{
			ebl->SetEnemyBullet(Chara.pos, f_bird.muki);
			f_bird.AnimPtn = 1;//球出しの時にした向く
		}

		//プレイヤーが自分より左にいたら左を右にいたら右を向く
		D3DXVECTOR2 plpos = game()->GetCm()->GetPlayer()->GetPlayerPos();
		if (plpos.x > Chara.pos.x)
		{
			f_bird.muki = 1;
		}
		else if (plpos.x < Chara.pos.x)
		{
			f_bird.muki = 0;
		}
	}


	
	f_bird.AnimCounter++;



	if (f_bird.survFlag == false && f_bird.AnimCounter >= 10)
	{
		gc =1;
		f_bird.AnimCounter = 0;
		if (f_bird.DeathPtn < 9)
			f_bird.DeathPtn++;

		if (f_bird.DeathPtn >= 9)
			f_bird.DeathPtn = 9;

	}
}

//移動処理
void Enemy_Bird::MoveBird()
{
	int gcc = GetCount();

	Chara.pos.y += Chara.vel.y;
	f_bird.MoveRangeB_Y += Chara.vel.y;

	if (fabs(f_bird.MoveRangeB_Y) >= 50)
	{
	 Chara.vel.y *= -1;
	}
	
}

void Enemy_Bird::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	BULLET* bl[MAX_BULLET];

	for (int i = 0; i < MAX_BULLET; i++)
		bl[i] = game()->GetBullet();


	if (f_bird.survFlag == 1)
	{
		DrawSpriteColor(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			128.0f, 128.0f,
			m_AnimTbl[f_bird.AnimPtn],g_MukiTbl[f_bird.muki],
			PATTERN_WIDTH,
			PATTERN_HEIGHT,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}

	else if (f_bird.survFlag == 0)
	{
		DrawSpriteColor(f_bird.m_TextureNo2,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			220.0f, 220.0f,
			m_DeathTbl[f_bird.DeathPtn], 0.0,
			0.1f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}