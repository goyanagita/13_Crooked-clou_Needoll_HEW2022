#include "Title.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"
#include "SceneChanger.h"
#include "fade.h"
#include "Option.h"
#include "sound.h"

void Title::Init()
{
	m_texture_bg   = LoadTexture((char*)"data/TEXTURE/TitleBg.png");
	m_texture_new  = LoadTexture((char*)"data/TEXTURE/New.png");
	m_texture_load = LoadTexture((char*)"data/TEXTURE/Load.png");
	m_texture_op   = LoadTexture((char*)"data/TEXTURE/Option.png");
	m_texture_exit = LoadTexture((char*)"data/TEXTURE/Exit.png");
	m_texture_title = LoadTexture((char*)"data/TEXTURE/needall.png");

	m_BGMNo = LoadSound((char*)"data/BGM/タイトル.wav");
	m_SENo = LoadSound((char*)"data/SE/タイトル選択後.wav");
	m_SENo2 = LoadSound((char*)"data/SE/ステージ選択移動.wav");


	pos_new = D3DXVECTOR2(580.0f, 150.0f);
	pos_load = D3DXVECTOR2(420.0f,165.0f);
	pos_op	 = D3DXVECTOR2(850.0f,150.0f);
	pos_exit = D3DXVECTOR2(100.0f,150.0f);
	pos_title = D3DXVECTOR2(285.0f,130.0f);

	pos_new_first = pos_new;
	pos_load_first = pos_load;
	pos_op_first = pos_op;
	pos_exit_first = pos_exit;

	vel_new	= D3DXVECTOR2(0.0f, -12.0f);
	vel_load = D3DXVECTOR2(0.0f, 0.0f);
	vel_op = D3DXVECTOR2(0.0f, -12.0f);
	vel_exit = D3DXVECTOR2(0.0f, 0.0f);


	SceneFadeIn();

	PlaySound(m_BGMNo, -1);

}

void Title::Uninit()
{
	StopSoundAll();

}

void Title::Update()
{
	frame++;

	switch (select_menu) {
	case MODE_NEW:
		ResetPosLoad();
		ResetPosOp();
		if (pos_new_first.y - pos_new.y <= 100) {
			pos_new.y -= MOVE_SPEED;
		}
		break;
	case MODE_OP:
		ResetPosExit();
		ResetPosNew();
		if (pos_op_first.y - pos_op.y <= 100) {
			pos_op.y -= MOVE_SPEED;
		}
		break;
	case MODE_LOAD:
		ResetPosNew();
		ResetPosExit();
		if (pos_load_first.y - pos_load.y <= 100) {
			pos_load.y -= MOVE_SPEED;
		}
		break;
	case MODE_EXIT:
		ResetPosLoad();
		ResetPosOp();
		if (pos_exit_first.y - pos_exit.y <= 100) {
			pos_exit.y -= MOVE_SPEED;
		}
		break;

	}
	if (op == nullptr) {
		if (GetKeyboardTrigger(DIK_UP) || (X_GetThumbLeftX(0) > 0 && frame >30)) {
			select_menu++;
			PlaySound(m_SENo2, 0);

			frame = 0;
			if (select_menu >= MODE_MAX)
				select_menu = MODE_EXIT;
		}
		if (GetKeyboardTrigger(DIK_DOWN) || (X_GetThumbLeftX(0) < 0 && frame > 30)) {
			select_menu--;
			PlaySound(m_SENo2, 0);

			frame = 0;
			if (select_menu <= -1)
				select_menu = MODE_OP;
		}
		if (GetKeyboardTrigger(DIK_SPACE) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) {

			switch (select_menu) {
			case MODE_EXIT:
				exit = true;
				break;
			case MODE_LOAD:

				break;
			case MODE_NEW:
				flag_new = true;
				break;
			case MODE_OP:
				flag_op = true;
				break;
			}
			PlaySound(m_SENo, 0);

		}
	}
	if (flag_new == true) {
		if (pos_new.y + (SCREEN_HEIGHT) > 0.0f) {
			vel_new.y += MOVE_UP;
			pos_new.y -= vel_new.y;
		}
		else {
			SceneTransition();
			if(GetColor() >= 1.0f)
				m_SceneChanger->ChangeScene(SceneChanger::eScene::SELECT);
		}
	}

	if (flag_op == true) {
		if (pos_op.y + (SCREEN_HEIGHT) > 0.0f) {
			vel_op.y += MOVE_UP;
			pos_op.y -= vel_op.y;
		}
		else {
			if (op == nullptr) {
				op = new Option;
				op->Init();
			}
			vel_op.y = 0.0f;
		}
		
		if (op != nullptr) {
			op->Update();

			if (op->GetExitOption() == true) {

				op->Uninit();
				if (op->GetFinish() == true) {
					
					if (pos_op.y != pos_op_first.y) {
						if (pos_op.y > pos_op_first.y) {
							vel_op.y -= MOVE_UP;
							if (pos_op.y <= pos_op_first.y) {
								pos_op = pos_op_first;
							}
						}
						if (pos_op.y < pos_op_first.y) {
							vel_op.y += MOVE_UP;
							pos_op.y += vel_op.y;
						}

						if (pos_op == pos_op_first) {

							flag_op = false;
							if (op != nullptr) {
								delete op;
								op = nullptr;
							}
						}
							
						
					}
					
				}
			}
		}

	}
}

void Title::Draw()
{
	DrawSprite(m_texture_bg, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);//最背面背景描画
	DrawSprite(m_texture_new, pos_new.x,pos_new.y,(256*3)/4,(1024*3)/4,0.0f,0.0f,1.0f,1.0f);
	DrawSprite(m_texture_load, pos_load.x, pos_load.y, (256 * 3) / 4, (1024 * 3) / 4, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(m_texture_op, pos_op.x, pos_op.y, (256 * 3) / 4, (1024 * 3) / 4,0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(m_texture_exit, pos_exit.x, pos_exit.y, (256 * 3) / 4, (1024 * 3) / 4,  0.0f, 0.0f, 1.0f, 1.0f);
	DrawSprite(m_texture_title, pos_title.x, pos_title.y, (128 * 4.2f), (512 * 2)/4,  0.0f, 0.0f, 1.0f, 1.0f);

	if (op != nullptr)
		op->Draw();
}

/*
タイトル修正案
糸巻きの上昇するスピードをもうちょっと自然に引っ張り上げられる感じにする

*/