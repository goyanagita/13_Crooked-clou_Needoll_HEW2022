#include "Switch.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "CharacterManager.h"
#include "collision.h"
#include "Player.h"
#include "PullBook.h"


SWITCH::SWITCH(class Game* game) :GameObject(game)
{

}

void SWITCH::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/book1.png");
	pos = D3DXVECTOR2(1500, 500.0f);
	first_pos = pos;
	sw_pos = D3DXVECTOR2(pos.x - 320.0f, pos.y);
	use = true;
	rot = 0.0f;
	int cnt = 0;
	vel = D3DXVECTOR2(2.0f, 0.0f);
	fool_flag = false;
	cm = game()->GetCm();
}

void SWITCH::Uninit(void)
{
}

void SWITCH::Update(void)
{

	D3DXVECTOR2 cp = game()->GetCm()->GetPlayer()->GetPlayerPos();
	D3DXVECTOR2 bp[MAX_BOOK_P];
	for (int i = 0; i < game()->GetOm()->GetTotalBookP(); i++) {
		bp[i] = game()->GetOm()->GetpBook(i)->GetPos();
		if (HitCheckBox(cp, 64.0f, 86.0f, sw_pos, 32.0f, 32.0f) || HitCheckBox(bp[i], 64.0f, 86.0f, sw_pos, 32.0f, 32.0f))
		{
			if (rot > -1.5f)
				rot -= 0.15f;
		}
		else
		{
			if (rot < 0.0f)
				rot += 0.15f;
		}
	}
}

void SWITCH::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//ÉuÉçÉbÉNÇÃï`âÊ
	DrawSpriteColorRotate(m_TextureNo,
		basePos.x + pos.x,
		basePos.y + pos.y,
		100.0f, 350.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rot);
}
