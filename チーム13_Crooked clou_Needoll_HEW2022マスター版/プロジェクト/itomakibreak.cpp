#include "itomakibreak.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "collision.h"
#include "Fieldcollision.h"
#include "MAP.h"
#include "Player.h"
#include "CharacterManager.h"
#include"Bullet.h"
#include "sound.h"

//static EXPLOSION	g_Itomakibreak[ITOMAKIBREAK_NUM];


ItomakiBreak::ItomakiBreak(class Game* game, D3DXVECTOR2 pos) :GameObject(game)
{
	m_pos = pos;
}

void ItomakiBreak::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/itomakibreak.png");
	m_TextureNo2 = LoadTexture((char*)"data/TEXTURE/ito_white.png");
	SENo = LoadSound((char*)"data/SE/本.wav");

	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);

	AnimCounter = 10;
	AnimPtn = 0;
	frame = 0;
}

void ItomakiBreak::Uninit(void)
{
}

void ItomakiBreak::Update(void)
{
	//針があたったときアニメーション
	if (broken == true)
	{
		if (frame > AnimCounter)
		{
			PlaySound(SENo, 0);

			//アニメーションパターンを一つ進める
			AnimPtn++;

			frame = 0;

			//最後のアニメーションパターンを表示したら消滅する
			if (AnimPtn >= 8)
			{
				broken = false;
				use = false;
				frame = 0;
				AnimPtn = 0;
			}
		}
		//時間経過
		frame += 1.0f;
	}
		//針と糸巻きの当たり判定

	//	ItomakiBreak*itomakibreak[ITOMAKIBREAK_NUM];
	//	for (int i = 0; i < game()->GetOm()->GetTotalBreak(); i++)itomakibreak[i] = game()->GetOm()->Getitomakibreak(i);

	if (use == true)
	{
		//糸巻と針の当たり判定
		if (HitCheckBox(m_pos, 70.0f, 70.0f, game()->GetBullet()->GetPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y))
		{
			use = false;
			broken = true;
		}

		//糸巻とプレイヤーの当たり判定
		Player* pPlayer = game()->GetCm()->GetPlayer();

		if (HitCheckBox(m_pos, 100.0f, 100.0f, pPlayer->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y))
		{
			if (HitCheckwallleft(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_pos, 40.0f, 50.0f))
			{
				pPlayer->Chara.pos.x = m_pos.x + 66.0f;
				pPlayer->Chara.moveinpulse = 0.0f;
				if (pPlayer->GetTarzanFlag() == true) {
					pPlayer->SetTarzan(false);
//					pBullet->SetCheck(false);
				}
			}
			else if (HitCheckwallright(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_pos, 40.0f, 50.0f))
			{
				pPlayer->Chara.pos.x = m_pos.x - 66.0f;
				pPlayer->Chara.moveinpulse = 0.0f;
				if (pPlayer->GetTarzanFlag() == true)
					pPlayer->SetTarzan(false);
//				pBullet->SetCheck(false);
			}
		}
	}
}

	


void ItomakiBreak::Draw(void)
{
	float AnimeTable[] =
	{
		0.0f,
		0.125f,
		0.25f,
		0.375f,
		0.5f,
		0.625f,
		0.75f,
		0.875f,
	};


	if (use == true)
	{
		D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo2,
			basePos.x + m_pos.x - 20.0f,
			basePos.y + m_pos.y - 10.0f,
			130.0f, 170.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			rot);


	

		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y + 20.0f,
			120.0f, 105.0f,
			AnimeTable[0],
			0.0f,
			0.125f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			rot);

	}

	if (broken == true)
	{

		D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo2,
			basePos.x + m_pos.x - 20.0f,
			basePos.y + m_pos.y - 10.0f,
			130.0f, 170.0f ,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			rot);

		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y + 20.0f,
			120.0f, 105.0f,
			AnimeTable[AnimPtn],
			0.0f,
			0.125f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			rot);
		
			/*DrawSprite(m_TextureNo, m_pos.x, m_pos.y, 64.0f, 64.0f, AnimCounter[itomakibreak], 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);*/
	}
}




