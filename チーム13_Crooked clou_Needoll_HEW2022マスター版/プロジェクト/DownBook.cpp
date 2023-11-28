#include "DownBook.h"
#include "Game.h"
#include "GameObject.h"
#include "CharacterManager.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "collision.h"



DOWNBOOK::DOWNBOOK(class Game* game, D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}

void DOWNBOOK::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/DownBook.png");
	first_pos = m_pos;
	rot = 0.0f;
	cnt = 0.0f;
	flag = false;
	use = true;
	vel = D3DXVECTOR2(2.0f, 0.0f);

	bl = game()->GetBullet();
}

void DOWNBOOK::Uninit(void)
{
}

void DOWNBOOK::Update(void)
{
	/*D3DXVECTOR2 cp = game()->GetCm()->GetPlayer()->GetPlayerPos();
	D3DXMATRIX mtx , mtxScl,mtxRot;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixScaling(&mtxScl, 32.0, 32.0, 0.0);
	mtx = mtx * mtxScl;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 1.5, 0.0, 0.0f);*/

	//’e‚Æ–{‚Ì“–‚½‚è”»’è
	if (HitCheckBox(m_pos, 64.0f, 86.0f, bl->GetPos(), 50.0f, 50.0f) && rot > -1.5f)
	{
		//if (GetKeyboardPress(DIK_Y) || X_GetThumbLeftX(0) < 0)
			/*D3DXMatrixRotationY(&mtx,1.5f);*/
			rot -= 0.13f;
	}

		if (rot < -0.13f)
			flag = true;

		if (flag == true)//flag‚ªŒš‚Á‚½‚çcount‚ð+‚µA
			cnt++;

		if (cnt > 120.0f)//120‚É‚È‚Á‚½‚çÁ‚·
			use = false;
	
}

void DOWNBOOK::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	
	if (use == true)
	{
		//–{‚Ì•`‰æ
		DrawSpriteColorRotate(m_TextureNo,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y,
			100.0f, 640.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),rot);
	}
}
