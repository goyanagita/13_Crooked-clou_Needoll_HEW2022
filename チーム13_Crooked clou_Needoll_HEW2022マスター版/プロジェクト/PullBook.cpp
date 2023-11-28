#include "PullBook.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "CharacterManager.h"
#include "Camera.h"
#include "collision.h"
#include "Player.h"



PULLBOOK::PULLBOOK(class Game* game, D3DXVECTOR2 pos) :GameObject(game)
{
	m_pos = pos;
}

void PULLBOOK::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/PullBook.png");
	
	first_pos = m_pos;
	use = true;
	rot = 0.0f;
	int cnt = 0;
	vel = D3DXVECTOR2(2.0f, 0.0f);
	fool_flag = false;
	pull_flag = false;
	cm = game()->GetCm();
}

void PULLBOOK::Uninit(void)
{
}

void PULLBOOK::Update(void)
{
	D3DXVECTOR2 cp = game()->GetCm()->GetPlayer()->GetPlayerPos();
	//‚±‚±‚ÌğŒ®‚ğj‚ª“–‚½‚Á‚Ä‚¢‚é‚É•Ï‚¦‚é
	if (GetKeyboardPress(DIK_Z))
		pull_flag = true;
	if (GetKeyboardPress(DIK_C))
		pull_flag = false;

	if (pull_flag == true)
	{
		if (cp.x < m_pos.x)
		{
			if (GetKeyboardPress(DIK_A) || X_GetThumbLeftX(0) < 0)
				m_pos.x -= 4.0f;
		}
		else if(cp.x > m_pos.x)
		{
			if(GetKeyboardPress(DIK_D) || X_GetThumbLeftX(0) > 0)
				m_pos.x += 4.0f;

		}
	}
}

void PULLBOOK::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//ƒuƒƒbƒN‚Ì•`‰æ
	DrawSpriteColorRotate(m_TextureNo,
		basePos.x + m_pos.x,
		basePos.y + m_pos.y,
		100.0f, 350.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rot);
}