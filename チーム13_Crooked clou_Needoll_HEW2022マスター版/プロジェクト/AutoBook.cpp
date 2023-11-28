#include "AutoBook.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "CharacterManager.h"
#include "Camera.h"
#include "collision.h"
#include "Player.h"

AUTOBOOK::AUTOBOOK(class Game * game,D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}

void AUTOBOOK::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/AutoBook.png");
	
	first_pos = m_pos;
	use = true;
	rot = 0.0f;
	int cnt = 0;
	vel = D3DXVECTOR2(2.0f, 0.0f);
	fool_flag = false;
	cm = game()->GetCm();
}

void AUTOBOOK::Uninit(void)
{
}

void AUTOBOOK::Update(void)
{
	D3DXVECTOR2 cp = game()->GetCm()->GetPlayer()->GetPlayerPos();
	if (HitCheckBox(cp, 64.0f, 86.0f, m_pos, 320.0f, 320.0f) && rot > -1.5f)
	{
		rot -= 0.13f;
	}
}

void AUTOBOOK::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//ƒuƒƒbƒN‚Ì•`‰æ
	DrawSpriteColorRotate(m_TextureNo,
		basePos.x + m_pos.x,
		basePos.y + m_pos.y,
		100.0f, 640.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rot);
}