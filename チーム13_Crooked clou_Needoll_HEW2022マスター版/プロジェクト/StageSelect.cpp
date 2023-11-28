//宮部追加
#include "StageSelect.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"
#include "SceneChanger.h"
#include "fade.h"
#include "sound.h"

void StageSelect::Init()
{
	m_texture_selectbg = LoadTexture((char*)"data/TEXTURE/stage1bg.png");
	m_texture_1st = LoadTexture((char*)"data/TEXTURE/stage1.png");
	m_texture_2nd = LoadTexture((char*)"data/TEXTURE/stage2.png");
	m_texture_3rd = LoadTexture((char*)"data/TEXTURE/stage3.png");
	m_texture_4th = LoadTexture((char*)"data/TEXTURE/stage4.png");
	m_texture_5th = LoadTexture((char*)"data/TEXTURE/stage5.png");

	m_texture_player = LoadTexture((char*)"data/TEXTURE/メインキャラ_チップ(修正）.png");
	m_SENo = LoadSound((char*)"data/SE/ステージ選択移動.wav");


	pos_1st = D3DXVECTOR2(70.0f, 450.0f);
	pos_2nd = D3DXVECTOR2(200.0f, 320.0f);
	pos_3rd = D3DXVECTOR2(440.0f, 250.0f);
	pos_4th = D3DXVECTOR2(550.0f, 245.0f);
	pos_5th = D3DXVECTOR2(620.0f, 240.0f);
	stage_now = 0;
	pos_player = D3DXVECTOR2(pos_1st.x, pos_1st.y - 90.0f);
	//SceneFadeIn();
}

void StageSelect::Uninit()
{
	StopSoundAll();

}

void StageSelect::Update()
{
	frame++;
	if (GetKeyboardTrigger(DIK_UP)||(X_GetThumbLeftX(0) > 0 && frame > 30)) {
		stg_select++;
		frame = 0;
		if (stg_select >= CC)
			stg_select = CC;//解放されているところを超えたら、それより先には進めない

		PlaySound(m_SENo, 0);

	}
	if (GetKeyboardTrigger(DIK_DOWN) || (X_GetThumbLeftX(0) < 0 && frame > 30)) {
		stg_select--;
		frame = 0;
		if (stg_select <= -1)
			stg_select = STG_1st;
		PlaySound(m_SENo, 0);

	}
	
	switch (stg_select) {
	case 0:
		pos_player = pos_1st;
		pos_player.y = pos_1st.y - 90.0f;
		break;
	case 1:
		pos_player = pos_2nd;
		pos_player.x += 100;
		pos_player.y = pos_2nd.y - 50.0f;
		break;
	case 2:
		pos_player = pos_3rd;
		pos_player.x += 130;
		pos_player.y = pos_3rd.y - 120.0f;
		break;
	case 3:
		pos_player = pos_4th;
		pos_player.x += 170.0f;
		pos_player.y = pos_4th.y - 20.0f;
		break;
	case 4:
		pos_player = pos_5th;
		pos_player.x += 185;
		pos_player.y = pos_5th.y - 40.0f;
		break;
	}


	if ((GetKeyboardTrigger(DIK_RETURN) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) && frame > 60) {
		
		switch (stg_select) {
		case STG_1st:
			SceneTransition();
				m_SceneChanger->ChangeScene(SceneChanger::eScene::GAME);
			break;

		case STG_2nd:
			if(flag_first == true)
				//本来ならステージ2に行く
				m_SceneChanger->ChangeScene(SceneChanger::eScene::GAME);
			break;

		case STG_3rd:
			if (flag_second == true)
				//本来ならステージ3に行く
				m_SceneChanger->ChangeScene(SceneChanger::eScene::TITLE);
			break;

		}
	}
	if (goal_check) {
		//このままだと再プレイでクリアしても進んじゃう
		CC++;
		if (CC > STG_5th) {
			CC = STG_5th;
		}
		switch (CC) {
		case 1:
			flag_first = true;
			break;
		case 2:
			flag_first = true;
			flag_second = true;
			break;
		case 3:
			flag_first = true;
			flag_second = true;
			flag_third = true;
			break;
		case 4:
			flag_first = true;
			flag_second = true;
			flag_third = true;
			flag_fourth = true;
			break;
		
		default:
			break;
		}
		goal_check = false;

	}
}

void StageSelect::Draw()
{
	DrawSprite(m_texture_selectbg, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);//最背面背景描画	
	DrawSprite(m_texture_1st, pos_1st.x, pos_1st.y, 256 / 2, 1024 / 8, 0.0f, 0.0f, 1.0f, 1.0f);

	if (flag_first == true)//1面クリアで描画
		DrawSprite(m_texture_2nd, pos_2nd.x, pos_2nd.y, (256) * 2, (1024) / 3, (1.0f / 8), (1.0f / 4) * 3, (1.0f / 8), (1.0f / 4));

	if (flag_second == true)//2面クリアで描画
		DrawSprite(m_texture_3rd, pos_3rd.x, pos_3rd.y, (256) * 2, (1024) / 3, (1.0f / 8) * 5, (1.0f / 4) * 3, (1.0f / 8), (1.0f / 4));

	if (flag_third == true)//3面クリアで描画
		DrawSprite(m_texture_4th, pos_4th.x, pos_4th.y, (256 * 2), (1024) / 3, (1.0f / 8), (1.0f / 4) * 3, (1.0f / 8), (1.0f / 4));

	if (flag_fourth == true)//4面クリアで描画
		DrawSprite(m_texture_5th, pos_5th.x, pos_5th.y, (256 * 2), (1024) / 3, (1.0f / 8), (1.0f / 4) * 3, (1.0f / 8), (1.0f / 4));

	DrawSprite(m_texture_player, pos_player.x, pos_player.y,
		32.0f*3.0f, 32.0f*4.5f,
		0.0f,
		1.0f / 24 + 0.001f,
		1.0f / 8,
		1.0f / 24);
}

