#include "Ladder.h"
#include "Game.h"
#include "Camera.h"
#include "collision.h"
Ladder::Ladder(class Game * game,D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}

void Ladder::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/ladder.png");
	pBullet = game()->GetBullet();
}

void Ladder::Uninit(void)
{
}

void Ladder::Update(void)
{
	if (HitCheckBox(pBullet->GetPos(), 64.0f, 86.0f, m_pos, 50.0f, 50.0f))
	{
		hit_bullet = true;
	}
}

void Ladder::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//ƒuƒƒbƒN‚Ì•`‰æ
	DrawSpriteColorRotate(m_TextureNo,
		basePos.x + m_pos.x,
		basePos.y + m_pos.y,
		198.0f, 1280.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0.0f);
}
