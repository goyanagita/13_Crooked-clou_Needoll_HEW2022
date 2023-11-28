#include "Pause.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"

void Pause::Init()
{
	m_textrue_no = LoadTexture((char*)"data/TEXTURE/option_.png");
	m_pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void Pause::Uninit()
{
}

void Pause::Update()
{
	if(GetKeyboardTrigger(DIK_F))
		exit_menu = true;
}

void Pause::Draw()
{
	DrawSprite(m_textrue_no, m_pos.x, m_pos.y, 721, 549, 0.0f, 0.0f, 1.0f, 1.0f);
}
