//���̒e----------------------------------------------------------------------
//Author�@Masaya Miyabe
//----------------------------------------------------------------------------

#include "EnemyBullet.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "CharacterManager.h"
#include "Block.h"
#include "collision.h"
#include "Enemy_Bird.h"
#include "ObjectManager.h"
#include "Player.h"

static float g_RotateTable[4] =
{
	D3DX_PI,		//������(180����]������)
	(-D3DX_PI / 2),	//������(-90����]������)
	(+D3DX_PI / 2),	//�E����(+90����]������)
	0.0f,			//�����
};

ENEMYBULLET::ENEMYBULLET(class Game * game) :GameObject(game)
{
	m_TextureF1 = LoadTexture((char*)"data/TEXTURE/feather.png");
	m_TextureF2 = LoadTexture((char*)"data/TEXTURE/feather2.png");
	use = false;

}

void ENEMYBULLET::Init()
{
	cm = game()->GetCm();

	for (int i = 0; i < MAX_BLOCK; i++){
		bl = game()->GetOm()->GetBlock(i);
	}
}

void ENEMYBULLET::Uninit()
{
}

void ENEMYBULLET::Update()
{
	Player* pl;
	pl = game()->GetCm()->GetPlayer();

	if (use == true) {
		//�e�̍��W�X�V
		m_pos.x += vel.x;
		m_pos.y -= vel.y;

		//�L���t���[�������炷
		frame--;

		//�L���t���[����0�ȉ��ɂȂ�������t���O���I�t�ɂ���
		if (frame <= 0)
		{
			use = false;
		}

		use = false;

		if (HitCheckBox(m_pos, 64.0f, 86.0f, pl->game()->GetCm()->GetPlayer()->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y) && use == true)
		{
			pl->SetHit(true);
		}
	}
}

void ENEMYBULLET::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	if (use == true) {
		switch (m_muki) {
		case 0:
			DrawSpriteColorRotate(m_TextureF1, basePos.x + m_pos.x, basePos.y + m_pos.y, 64.0f, 64.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		case 1:
			DrawSpriteColorRotate(m_TextureF2, basePos.x + m_pos.x, basePos.y + m_pos.y, 64.0f, 64.0f,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
			break;
		}
	}
	if (m_pos.y >= 350.0f)
	{
		use == false;
	}
}

void ENEMYBULLET::SetEnemyBullet(D3DXVECTOR2 pos, int muki)
{
		for (int i = 0; i < BIRD_MAX; i++)
		{
			eb = cm->GetBird(i);

			if (use == false) {
				m_pos = pos;
				m_muki = muki;
				switch (m_muki) {
				case 0://������
					vel = D3DXVECTOR2(-BULLET_SPEED, -6.0f);
					vel.x += eb->speed();
					gravity = D3DXVECTOR2(0.3f, 0.2f);
					break;
				case 1://�E����
					vel = D3DXVECTOR2(BULLET_SPEED, -6.0f);
					vel.x += eb->speed();
					gravity = D3DXVECTOR2(0.3f, 0.2f);
					break;
				}
				height = 0.0f; //��őΉ�����

				//�L���t���[�����Z�b�g
				frame = 65;

				//���t���O�I��
				use = true;

			}
		}
	}


