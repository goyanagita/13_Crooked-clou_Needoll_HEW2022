#include "Block.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "collision.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "CharacterManager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
BLOCK::BLOCK(class Game* game, D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}
//=============================================================================
// 初期化処理
//=============================================================================
void BLOCK::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/Tarzan.png");
	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);
	
}
//=============================================================================
// 終了処理
//=============================================================================
void BLOCK::Uninit(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void BLOCK::Update(void)
{
	Player* pl;
	pl = game()->GetCm()->GetPlayer();
	pBullet = game()->GetBullet();

	if (pBullet->GetUse()) {
		//弾とブロックの当たり判定
		if (HitCheckBox(pBullet->GetPos(), 64.0f, 86.0f, m_pos, 50.0f, 50.0f) && hit_bullet == false)
		{
			hit_bullet = true;
			pl->ChanegeState(Player::Player_state::BLOCK_STING);
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void BLOCK::Draw(void)
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
