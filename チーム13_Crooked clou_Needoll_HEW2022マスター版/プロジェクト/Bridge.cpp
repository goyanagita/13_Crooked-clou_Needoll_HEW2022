#include "Bridge.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "collision.h"
#include "Player.h"
#include "CharacterManager.h"
#include "Game.h"
#include "Map.h"
#include "inputx.h"
#include "sound.h"
#include "ThreadGauge.h"

static float g_AnimeTable[4] =
{
	0.0f,
	0.33333f,
	0.66667f,
	0.33333f,
};

Bridge::Bridge(class Game * game, D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}

void Bridge::Init(void)
{
	m_TexturePo1 = LoadTexture((char*)"data/TEXTURE/poal3.png");
	m_TextureBr1 = LoadTexture((char*)"data/TEXTURE/bridge1.png");
	m_TextureBr2 = LoadTexture((char*)"data/TEXTURE/bridge2.png");
	m_SENo = LoadSound((char*)"data/SE/ƒ^ƒCƒgƒ‹‘I‘ðŒã.wav");

}

void Bridge::Uninit(void)
{
}

void Bridge::Update(void)
{

	D3DXVECTOR2 plpos = game()->GetCm()->GetPlayer()->GetPlayerPos();
	Player* pPlayer = game()->GetCm()->GetPlayer();
	D3DXVECTOR2 pLen = game()->GetBullet()->GetLen();
	

	if (AnimCounter >= 7) {

		if (GetKeyboardPress(DIK_F)|| X_IsButtonPressed(0,XINPUT_GAMEPAD_Y)) {
			AnimPtn++;
			PlaySound(m_SENo, 0);
			if (pLen.x <= 8.0f * 32.0f)//’Z‚¢‹´‚ÌŽž
			{
				if (AnimPtn >= 29) {
					AnimPtn = 34;//‹´‚ÌŠ®¬

					build_s = true;
					game()->GetTg()->UseThread(USE_BRIDGE);

					StopSoundAll();
				}
			}
			else if (pLen.x >= 12.0f* 32.0f) {//’·‚¢‹´‚ÌŽž
				if (AnimPtn >= 35) {
					AnimPtn = 40;//‹´‚ÌŠ®¬

					game()->GetTg()->UseThread(USE_BRIDGE);

					build_l = true;

					

					StopSoundAll();
				}
			}
		}
		if (GetKeyboardPress(DIK_T)) {
			build_s = false;
			AnimPtn = 0;

		}
		else if (GetKeyboardPress(DIK_V)|| X_IsButtonPressed(0, XINPUT_GAMEPAD_B)&& build_l != false) {
			build_l = false;
			AnimPtn = 0;

			game()->GetTg()->UseThread(-MAX_THREAD);


		}

		AnimCounter = 0;
	}
	AnimCounter++;
}

void Bridge::Draw(void)
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	D3DXVECTOR2 pLen = game()->GetBullet()->GetLen();

	//’Z‚ßƒ|[ƒ‹‚Ì•`‰æ
	if (pBullet->GetHitPoal() && build_s == false && build_l == false)
	{
		DrawSpriteColorRotate(m_TexturePo1,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y,
			25.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
			0.0f);
	}
	else
	{
		DrawSpriteColorRotate(m_TexturePo1,
			basePos.x + m_pos.x,
			basePos.y + m_pos.y,
			25.0f, 100.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0.0f);
	}



	//’Z‚ß‹´‚Ì•`‰æ
	for (int i = 1; i < BRIDGE_POAL; i++)
	{
		if (i % 2 == 0)
		{
			if (hit == true && pLen.x <= 8 * 32.0f)//’Œ‚É“–‚½‚Á‚Ä‚é
			{
				if (GetKeyboardPress(DIK_F) || X_IsButtonPressed(0, XINPUT_GAMEPAD_Y) && build_s == false)//–D‚¤ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚é
				{
					DrawSpriteColorRotate(m_TextureBr1,
						basePos.x + m_pos.x - 128,
						basePos.y + m_pos.y - 40,
						448.0f, 256.0f,
						0.0588235294117647f*(AnimPtn % 17),
						0.5f*(AnimPtn / 17),
						0.0588235294117647f,
						1.0f / 2,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f);
				}

				else if (AnimPtn < 34) {
					AnimPtn = 0;
				}

				else if (AnimPtn == 34 && build_s == true) {
					DrawSpriteColorRotate(m_TextureBr1,
						basePos.x + m_pos.x - 128,
						basePos.y + m_pos.y - 40,
						448.0f, 256.0f,
						(0.0588235294117647f * 16),
						1.0f / 2,
						0.0588235294117647f,
						1.0f / 2,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f);
				}

			}
		}

	}

	//’·‚ß‹´‚Ì•`‰æ
	for (int i = 0; i < BRIDGE_POAL; i++)
	{
		if (i % 2 == 1)
		{
			if (hit == true && pLen.x >= 13.0f * 32.0f)//’Œ‚É“–‚½‚Á‚Ä‚é
			{
				if (GetKeyboardPress(DIK_F) || X_IsButtonPressed(0, XINPUT_GAMEPAD_Y) && build_l == false)//–D‚¤ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚é
				{
					DrawSpriteColorRotate(m_TextureBr2,
						basePos.x + m_pos.x - 220,
						basePos.y + m_pos.y - 40,
						660.0f, 256.0f,
						0.1f*(AnimPtn % 10),
						0.25f*(AnimPtn / 10),
						0.1,
						1.0f / 4,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f);
				}

				else if (AnimPtn < 35) {
					AnimPtn = 0;
				}

				else if (AnimPtn == 40 && build_l == true) {
					DrawSpriteColorRotate(m_TextureBr2,
						basePos.x + m_pos.x - 220,
						basePos.y + m_pos.y - 40,
						660.0f, 256.0f,
						(0.1f * 9),
						0.75f,
						0.1f,
						1.0f / 4,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f);
				}

			}
		}

	}
	
}
