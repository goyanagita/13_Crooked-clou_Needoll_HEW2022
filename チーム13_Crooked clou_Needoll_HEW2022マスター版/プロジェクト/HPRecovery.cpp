#include "HPRecovery.h"
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

HPRecovery::HPRecovery(class Game* game,D3DXVECTOR2 pos) :GameObject(game)
{
	m_pos = pos;
}

void HPRecovery::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/hp.png");
	//m_pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 380.0f);
	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(0.0f, 0.0f);
}

void HPRecovery::Uninit(void)
{
}

void HPRecovery::Update(void)
{
	Player* pPlayer = game()->GetCm()->GetPlayer();

	//プレイヤーとアイテムの当たり判定
	if (HitCheckBox(m_pos, 70.0f, 70.0f, pPlayer->GetPlayerPos(), 32.0f, 32.0f))
	{

		//アイテムを消す
		use = false;
		//ゲージが増える
		pPlayer->Life(1);
	}
}

void HPRecovery::Draw(void)
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
			0.0f);
	}
}