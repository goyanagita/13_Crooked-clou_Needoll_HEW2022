#include "Life.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "Player.h"
#include "CharacterManager.h"

#define DIVIDE_X 3	//���̕�����
#define DIVIDE_Y 1	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static float g_AnimeTable[4] =
{
	0.0f,
	0.33333333f,
	0.33333333f * 2,
	0.33333333f * 3,
};

Life::Life(class Game * game) :GameObject(game)
{
}

void Life::Init(void)
{
	m_texture_no = LoadTexture((char*)"data/TEXTURE/life.png");
	thread_cap = thread_cap_max;
	m_pos = D3DXVECTOR2(32.0f, 32.0f);
	view_gauge = 0;
}

void Life::Uninit(void)
{
}

void Life::Update(void)
{
	life = game()->GetCm()->GetPlayer()->hp();
	view_gauge = life ;
}

void Life::Draw(void)
{
	//f64.0f�Ŏ��������炵�Ă�(���ɂ��炷�Ȃ�m_pos.y�̂Ƃ���ɕς��Ă�)
	DrawSprite(m_texture_no, m_pos.x + 64.0f + ((64.0f / 3.0f) * life), m_pos.y, 
		64.0f * life, 64.0f, g_AnimeTable[view_gauge],
		0.0f, PATTERN_WIDTH * life, PATTERN_HEIGHT);
}
