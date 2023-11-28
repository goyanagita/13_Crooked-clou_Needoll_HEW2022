#include "itomaki.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "collision.h"
#include "Fieldcollision.h"
#include "MAP.h"
#include "Player.h"
#include "CharacterManager.h"


ITOMAKI::ITOMAKI(class Game* game, D3DXVECTOR2 pos) :GameObject(game)
{
	m_pos = pos;
}

void ITOMAKI::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/itomaki_red.png");
	
	first_pos = m_pos;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);
}

void ITOMAKI::Uninit(void)
{
}

void ITOMAKI::Update(void)
{
	//������
	m_pos.y *= 1.008;//8
	m_pos.x += 1.0;

	//����
	
	//��]
	rot += 0.1;
	

	for (int y = 0; y < MAX_YMAP; y++)
	{
		for (int x = 0; x < MAX_XMAP; x++)
		{
			D3DXVECTOR2 collipos = game()->map()->GetMeshColliPos(x, y);
			if (HitCheckBox(m_pos, 70.0f, 70.0f, collipos, 32.0f, 32.0f))
			{
				//�n��
				if (HitCheckField(m_pos, 64.0f, 64.0f, collipos, 32.0f, 32.0f))
				{
					//������������
					//use = false;
					m_pos = first_pos;
				}
				//����
				else if (HitCheckwallleft(m_pos, 64.0f, 64.0f, collipos, 32.0f, 32.0f))
				{
					//������������
					use = false;
				}
				//�E��
				else if (HitCheckwallright(m_pos, 64.0f, 64.0f, collipos, 32.0f, 32.0f))
				{
					//������������
				}
				//�V��
				//else if (HitCheckCelling(pos, 64.0f, 64.0f, collipos, 32.0f, 32.0f))
				//{
				//}
			}
		}
	}
	Player* pPlayer = game()->GetCm()->GetPlayer();
	//�����ƃv���C���[�̓����蔻��
	if (HitCheckBox(m_pos, 70.0f, 70.0f, pPlayer->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y))
	{

		//������������
		use = false;
		/*	broken = true;*/


	}

}

void ITOMAKI::Draw(void)
{
	if (use == true)
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
			rot);
	}
	if (broken == true)
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
			rot);
	}
}