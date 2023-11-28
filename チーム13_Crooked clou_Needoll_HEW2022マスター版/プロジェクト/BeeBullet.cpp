//�I�̒e----------------------------------------------------------------------
//�z�[�~���O�e
//Author�@Masaya Miyabe
//----------------------------------------------------------------------------

#include "BeeBullet.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "CharacterManager.h"
#include "Block.h"
#include "collision.h"
#include "Enemy_Bee.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Player.h"

static float g_RotateTable[4] =
{
	D3DX_PI,		//������(180����]������)
	(-D3DX_PI / 2),	//������(-90����]������)
	(+D3DX_PI / 2),	//�E����(+90����]������)
	0.0f,			//�����
};

BEEBULLET::BEEBULLET(class Game * game) :GameObject(game)
{
	
	bbullet.m_TextureS1 = LoadTexture((char*)"data/TEXTURE/�j.png");
	bbullet.m_TextureS2 = LoadTexture((char*)"data/TEXTURE/sting2.png");
	bbullet.use = false;

}

void BEEBULLET::Init()
{
	cm = game()->GetCm();
}

void BEEBULLET::Uninit()
{
}

void BEEBULLET::Update()
{
	BLOCK * bl[MAX_BLOCK];
	Player* pl;
	for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++)
	{
		bl[i] = game()->GetOm()->GetBlock(i);
	}
	pl = game()->GetCm()->GetPlayer();
	

	if (bbullet.use == true) {
		//�e�̍��W�X�V
		bbullet.m_pos.x += (bbullet.vel.x * 1.2f);
		bbullet.m_pos.y -= bbullet.vel.y;

		//�L���t���[�������炷
		bbullet.frame--;

		//�L���t���[����0�ȉ��ɂȂ�������t���O���I�t�ɂ���
		if (bbullet.frame <= 0)
		{
			bbullet.use = false;
		}
	}

	for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++) {
		if (HitCheckBox(bbullet.m_pos, 64.0f, 86.0f, bl[i]->game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f) && bbullet.use == true)
		{
			bbullet.check_eb = true;
		}
		else {
			bbullet.check_eb = false;
		}
	}

	if (HitCheckBox(bbullet.m_pos, 64.0f, 32.0f, pl->game()->GetCm()->GetPlayer()->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y)&& bbullet.use)
	{
		pl->SetHit(true);
	}


	
}

void BEEBULLET::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	switch (bbullet.m_muki)
	{
	case 0:
		DrawSpriteColorRotate(bbullet.m_TextureS1, basePos.x + bbullet.m_pos.x, basePos.y + bbullet.m_pos.y + 50, 50.0f, 50.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		break;
	case 1:
		DrawSpriteColorRotate(bbullet.m_TextureS2, basePos.x + bbullet.m_pos.x, basePos.y + bbullet.m_pos.y + 50, 50.0f, 50.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);
		break;
	}
}

void BEEBULLET::SetBeeBullet(D3DXVECTOR2 pos, int muki)
{
	Enemy_Bee* eb;

	if (bbullet.check_eb == false)
	{
		for (int i = 0; i < B_BULLET; i++)
		{
			eb = cm->GetBee(i);

			if (bbullet.use == false) {
				bbullet.m_pos = pos;
				bbullet.m_muki = muki;
				switch (bbullet.m_muki) {
				case 0://������
					bbullet.vel = D3DXVECTOR2(-BULLET_SPEED, -6.0f);
					bbullet.gravity = D3DXVECTOR2(0.2f, 0.1f);
					break;
				case 1://�E����
					bbullet.vel = D3DXVECTOR2(BULLET_SPEED, -6.0f);
					bbullet.gravity = D3DXVECTOR2(0.2f, 0.1f);
					break;
				}
				bbullet.height = 0.0f; //��őΉ�����

				//�L���t���[�����Z�b�g
				bbullet.frame = 65;

				//���t���O�I��
				bbullet.use = true;
			}
		}
	}
}
