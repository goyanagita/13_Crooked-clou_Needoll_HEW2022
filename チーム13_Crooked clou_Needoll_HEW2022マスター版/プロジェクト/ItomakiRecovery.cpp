#include "ItomakiRecovery.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "collision.h"
#include "Fieldcollision.h"
#include "MAP.h"
#include "player.h"
#include "Game.h"
#include "CharacterManager.h"
#include "ThreadGauge.h"

ItomakiRecovery::ItomakiRecovery(class Game* game,D3DXVECTOR2 pos) :GameObject(game)
{
	m_pos = pos;
}

void ItomakiRecovery::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/takara.png");
	//m_pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 450.0f);
	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);
}

void ItomakiRecovery::Uninit(void)
{
}

void ItomakiRecovery::Update(void)
{
	////放物線
	//pos.y *= 1.008;//8
	//pos.x += 1.0;

	////加速

	////回転
	//rot += 0.1;

	
	Player* pPlayer = game()->GetCm()->GetPlayer();


	if (HitCheckBox(m_pos, 70.0f, 70.0f, pPlayer->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y))
	{

		//糸巻きを消す
		use = false;
		//ゲージが増える
		game()->GetTg()->UseThread(-50);
		//ThreadGauge()->thread_cap();
		// UseThread(int use) { thread_cap -= use; };

	}
}

void ItomakiRecovery::Draw(void)
{
	if (use == true)
	{
		D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

		//ブロックの描画
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y,
			50.0f, 50.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			rot);
	}
}