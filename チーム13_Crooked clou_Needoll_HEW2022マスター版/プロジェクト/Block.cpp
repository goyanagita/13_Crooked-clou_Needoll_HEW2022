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
// �R���X�g���N�^
//=============================================================================
BLOCK::BLOCK(class Game* game, D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}
//=============================================================================
// ����������
//=============================================================================
void BLOCK::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/Tarzan.png");
	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);
	
}
//=============================================================================
// �I������
//=============================================================================
void BLOCK::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void BLOCK::Update(void)
{
	Player* pl;
	pl = game()->GetCm()->GetPlayer();
	pBullet = game()->GetBullet();

	if (pBullet->GetUse()) {
		//�e�ƃu���b�N�̓����蔻��
		if (HitCheckBox(pBullet->GetPos(), 64.0f, 86.0f, m_pos, 50.0f, 50.0f) && hit_bullet == false)
		{
			hit_bullet = true;
			pl->ChanegeState(Player::Player_state::BLOCK_STING);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void BLOCK::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//�u���b�N�̕`��
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
