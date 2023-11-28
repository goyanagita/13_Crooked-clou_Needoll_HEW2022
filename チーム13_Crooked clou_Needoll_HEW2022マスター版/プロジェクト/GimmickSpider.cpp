//お邪魔蜘蛛----------------------------------------------------------------------
//プレイヤーが近づくと垂れてくる　死ぬ
//作成者　Masaya Miyabe
//----------------------------------------------------------------------------

#include "GimmickSpider.h"
#include "Game.h"
#include "CharacterManager.h"

#define DROP_SPEED 15.0f

void GimmickSpider::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/spider.png");
	Chara.pos = D3DXVECTOR2(1500.0f, 100.f);
	Chara.hp = 1;
}

void GimmickSpider::Update() 
{
	D3DXVECTOR2 plpos = game()->GetCm()->GetPlayer()->GetPlayerPos();

	if(plpos.x == 960.0f)
	{ 
		Chara.pos.y += DROP_SPEED;

	}
}

void GimmickSpider::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();



	if (g_spider.survFlag == 1)
	{
		DrawSpriteColor(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			128.0f, 128.0f,
			1.0f, 1.0f,
			PATTERN_WIDTH,
			PATTERN_HEIGHT,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
