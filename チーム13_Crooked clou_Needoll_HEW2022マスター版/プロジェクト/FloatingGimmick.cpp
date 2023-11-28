#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "CharacterManager.h"
#include "collision.h"
#include "Player.h"
#include "FloatingGimmick.h"


FLGIMMICK::FLGIMMICK(class Game * game,D3DXVECTOR2 pos) :GameObject(game)
{
	
}

void FLGIMMICK::Init(void)
{
	
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/book1.png");
	//こっちが赤色の浮遊ギミック
	for (int i = 0; i < MAX_GIMMICK/2; i++)
	{
		g_Gimmick[i].pos = D3DXVECTOR2(1500, 500.0f + (-250.f * i));
		g_Gimmick[i].first_pos = g_Gimmick[i].pos;
		g_Gimmick[i].use = true;
		g_Gimmick[i].rot = 0.0f;
		g_Gimmick[i].vel = D3DXVECTOR2(2.0f, 0.0f);
		cm = game()->GetCm();
	}
	//こっちが青色の浮遊ギミック
	for (int i = MAX_GIMMICK / 2; i < MAX_GIMMICK; i++)
	{
		g_Gimmick[i].pos = D3DXVECTOR2(750, 500.0f + (-250.f * (i - MAX_GIMMICK / 2)));
		g_Gimmick[i].first_pos = g_Gimmick[i].pos;
		g_Gimmick[i].use = true;
		g_Gimmick[i].rot = 0.0f;
		g_Gimmick[i].vel = D3DXVECTOR2(2.0f, 0.0f);
		cm = game()->GetCm();
	}
}


void FLGIMMICK::Uninit(void)
{


}

void FLGIMMICK::Update(void)
{
	D3DXVECTOR2 cp = game()->GetCm()->GetPlayer()->GetPlayerPos();
	for (int i = 0; i < MAX_GIMMICK/2; i++)
	{
		g_Gimmick[i].pos.x -= 10.0f;//浮遊ギミックのスピード
		g_Gimmick[i].rot -= 1.0f;//回転機能いらなかったら消してね

		if (HitCheckBox(cp, 64.0f, 86.0f, g_Gimmick[i].pos, 32.0f, 32.0f))
		{
			g_Gimmick[i].use = false;
			game()->GetCm()->GetPlayer()->Life(1);//player.hにvoid Life(int life) { Chara.hp += life; }を作ったのでよろしく
		}


		if (g_Gimmick[i].pos.x < 0)
		{
			g_Gimmick[i].use = true;
			g_Gimmick[i].pos.x = RIGHT_END;
		}
	}
	for (int i = MAX_GIMMICK / 2; i < MAX_GIMMICK; i++)
	{

		g_Gimmick[i].pos.x -= 10.0f;
		g_Gimmick[i].rot -= 1.0f;

		if (HitCheckBox(cp, 64.0f, 86.0f, g_Gimmick[i].pos, 32.0f, 32.0f))
		{
			g_Gimmick[i].use = false;
			game()->GetCm()->GetPlayer()->SetPosX(-5.0f);//プレイヤーをノックバックさせる
		}


		if (g_Gimmick[i].pos.x < 0)
		{
			g_Gimmick[i].use = true;
			g_Gimmick[i].pos.x = RIGHT_END;
		}
	}
}

void FLGIMMICK::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	for (int i = 0; i < MAX_GIMMICK/2; i++)
	{
		if (g_Gimmick[i].use == false)
			continue;
		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + g_Gimmick[i].pos.x,
			basePos.y + g_Gimmick[i].pos.y,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),g_Gimmick[i].rot);
	}
	for (int i = MAX_GIMMICK / 2; i < MAX_GIMMICK; i++)
	{
		if (g_Gimmick[i].use == false)
			continue;
		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + g_Gimmick[i].pos.x,
			basePos.y + g_Gimmick[i].pos.y,
			100.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), g_Gimmick[i].rot);
	}
}
