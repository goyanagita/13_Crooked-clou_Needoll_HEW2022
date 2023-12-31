#include "Enemy_Field.h"
#include "GameObject.h"
#include "Game.h"
#include "Character.h"
#include "CharacterManager.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"

#define DIVIDE_X 8
#define DIVIDE_Y 4
#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)


//static int g_KumaTexture;

static float g_MukiTbl[4]
{
	0.0f,
	0.25f,
	0.5f,
	0.75f
};


//===================================================================
// 初期化処理
//===================================================================
void Enemy_Field::Init()
{
		Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/クマ4.png");
		f_enemy.m_TextureNo2 = LoadTexture((char*)"data/TEXTURE/deathbear.png");
		Chara.vel = D3DXVECTOR2(1.2f, 0.0f);
		f_enemy.AnimPtn = 0;
		f_enemy.DeathPtn = 0;
		f_enemy.muki = 1;
		f_enemy.survFlag = true;//0なら死亡
		Chara.hp = 3;
	

}
//===================================================================
// 更新処理
//===================================================================
void Enemy_Field::Update()
{
	if (f_enemy.survFlag == true)
    {
		MoveEnemy();
		if (f_enemy.AnimCounter > 10) {
			f_enemy.AnimPtn++;
			if (f_enemy.AnimPtn >= 8)
				f_enemy.AnimPtn = 0;
			f_enemy.AnimCounter = 0;
		}
	}


	if (f_enemy.survFlag == false && f_enemy.AnimCounter >= 10)
	{
		f_enemy.AnimCounter = 0;
		if (f_enemy.DeathPtn < 9)
			f_enemy.DeathPtn++;

		if(f_enemy.DeathPtn >= 9)
			f_enemy.DeathPtn = 9;
				
	}

	f_enemy.AnimCounter++;
		
}

//===================================================================
// 移動処理
//===================================================================
void Enemy_Field::MoveEnemy()
{
	Chara.pos.x -= Chara.vel.x;


	
}
//===================================================================
// 描画処理
//===================================================================
void Enemy_Field::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	BULLET* bl[MAX_BULLET];

	for (int i = 0; i < MAX_BULLET; i++)
		bl[i] = game()->GetBullet();
	
	if (f_enemy.survFlag == 1)//
	{
		DrawSpriteColor(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			150.0f, 150.0f,
			m_AnimTbl[f_enemy.AnimPtn], 1.0f,
			PATTERN_WIDTH,
			PATTERN_HEIGHT,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		
	}

	if (f_enemy.survFlag == 0)
	{
		DrawSpriteColor(f_enemy.m_TextureNo2,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			280.0f, 280.0f,
			m_DeathTbl[f_enemy.DeathPtn], 0.0,
			0.1f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
}
