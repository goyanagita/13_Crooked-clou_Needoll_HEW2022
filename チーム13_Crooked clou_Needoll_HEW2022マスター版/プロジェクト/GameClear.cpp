#include "GameClear.h"
//ŽR“à’Ç‰Á
#include "GameClear.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"
#include "SceneChanger.h"
#include "fade.h"
#include "Game.h"
#include "GameObject.h"
#include "sound.h"

void GameClear::Init()
{
	m_texture_gameclear = LoadTexture((char*)"data/TEXTURE/gameclear.png");
	m_texture_gameclear2 = LoadTexture((char*)"data/TEXTURE/clearbg.png");
	BGMNo = LoadSound((char*)"data/BGM/gameclear.wav");

	//SceneFadeIn();

	
}

void GameClear::Uninit()
{
	StopSoundAll();
}

void GameClear::Update()
{
		if (GetKeyboardTrigger(DIK_RETURN) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A))
		m_SceneChanger->ChangeScene(SceneChanger::eScene::SELECT);

		if(g_AnimeCounter == 11)
		PlaySound(BGMNo, 0);
}

void GameClear::Draw()
{
	DrawSprite(m_texture_gameclear2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f , 0.0f, 1.0f, 1.0f);//Å”w–Ê”wŒi•`‰æ	
	DrawSprite(m_texture_gameclear, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f / 8 * g_AnimePtn, 1.0f / 6 * g_AnimePtn2, 1.0f / 8, 1.0f / 6);//Å”w–Ê”wŒi•`‰æ	
	

	if (frame++ > 1.5)
	{

		if (g_AnimeCounter < 47)
		{
			g_AnimePtn++;
			//ÅŒã‚ÌƒAƒjƒ[ƒVƒ‡ƒ“ƒpƒ^[ƒ“‚ð•\Ž¦‚µ‚½‚çƒŠƒZƒbƒg‚·‚é

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
		frame = 0;
	}

	if (g_AnimeCounter > 48)
	{

	}
}

