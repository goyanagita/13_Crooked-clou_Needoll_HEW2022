//éRì‡í«â¡
#include "GameOver.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"
#include "SceneChanger.h"
#include "fade.h"
#include "Game.h"
#include "GameObject.h"
#include "sound.h"

void GameOver::Init()
{
	m_texture_gameover = LoadTexture((char*)"data/TEXTURE/gameover.png");
	m_texture_gameover2 = LoadTexture((char*)"data/TEXTURE/Back.png");
	m_texture_retry = LoadTexture((char*)"data/TEXTURE/retry1.png");
	m_texture_retry2 = LoadTexture((char*)"data/TEXTURE/retry2.png");
	m_texture_select = LoadTexture((char*)"data/TEXTURE/select1.png");
	m_texture_select2 = LoadTexture((char*)"data/TEXTURE/select2.png");
	BGMNo = LoadSound((char*)"data/BGM/gameover.wav");
	m_SENo2 = LoadSound((char*)"data/SE/ÉXÉeÅ[ÉWëIëà⁄ìÆ.wav");


	pos_retry = D3DXVECTOR2(SCREEN_WIDTH / 2, 350.0f);
	pos_retry2 = D3DXVECTOR2(SCREEN_WIDTH / 2, 350.0f);
	pos_select = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);
	pos_select2 = D3DXVECTOR2(SCREEN_WIDTH / 2, 400.0f);

	PlaySound(BGMNo, -1);

}

void GameOver::Uninit()
{
	StopSoundAll();
}

void GameOver::Update()
{
	frame++;

	if (select_flag == true)
	{
		if (GetKeyboardTrigger(DIK_UP) || (X_GetThumbLeftY(0) > 0 && frame > 30)) {
			select_flag = false;
			PlaySound(m_SENo2, 0);
			frame = 0;
		}
		else if (GetKeyboardTrigger(DIK_RETURN) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A))
		m_SceneChanger->ChangeScene(SceneChanger::eScene::SELECT);
	}
	if (select_flag == false)
	{
		if (GetKeyboardTrigger(DIK_DOWN) || (X_GetThumbLeftY(0) < 0 && frame > 30)) {
			select_flag = true;
			PlaySound(m_SENo2, 0);
			frame = 0;
		}

		else if (GetKeyboardTrigger(DIK_RETURN) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A))
			m_SceneChanger->ChangeScene(SceneChanger::eScene::GAME);
	}
}

void GameOver::Draw()
{
	DrawSprite(m_texture_gameover2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f / 8 * g_AnimePtn, 1.0f / 6 * g_AnimePtn2, 1.0f / 8, 1.0f / 6);//ç≈îwñ îwåiï`âÊ	
	DrawSprite(m_texture_gameover, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f / 8 * g_AnimePtn, 1.0f / 6 * g_AnimePtn2, 1.0f / 8, 1.0f / 6);//ç≈îwñ îwåiï`âÊ	
	if (g_AnimeCounter > 47 && select_flag == true)
	{
		DrawSprite(m_texture_retry, pos_retry.x, pos_retry.y, 900.0f /3 , 400.0f /3, 0.0f, 0.0f, 1.0f, 1.0f);//ç≈îwñ îwåiï`âÊ	
		DrawSprite(m_texture_select2, pos_select2.x, pos_select2.y, 900.0f / 3, 400.0f / 3, 0.0f, 0.0f, 1.0f, 1.0f);//ç≈îwñ îwåiï`âÊ	
	}
	else if (g_AnimeCounter > 47 && select_flag == false)
	{
		DrawSprite(m_texture_retry2, pos_retry2.x, pos_retry2.y, 900.0f / 3, 400.0f / 3, 0.0f, 0.0f, 1.0f, 1.0f);//ç≈îwñ îwåiï`âÊ	
		DrawSprite(m_texture_select, pos_select.x, pos_select.y, 900.0f / 3, 400.0f / 3, 0.0f, 0.0f, 1.0f, 1.0f);//ç≈îwñ îwåiï`âÊ	
	}
	else if (frame % 5 == 0)
	{
		
		if (g_AnimeCounter < 47)
		{
			g_AnimePtn++;
			//ç≈å„ÇÃÉAÉjÉÅÅ[ÉVÉáÉìÉpÉ^Å[ÉìÇï\é¶ÇµÇΩÇÁÉäÉZÉbÉgÇ∑ÇÈ

			if (g_AnimePtn >= 8)
			{
				if (g_AnimePtn2 > 6)
				{

				}
				g_AnimePtn = 0;
				g_AnimePtn2++;
			}
		}

		g_AnimeCounter++;
	}

	if (g_AnimeCounter > 48)
	{

	}
}

