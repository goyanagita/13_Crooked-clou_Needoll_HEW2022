#include "goal.h"
#include "Game.h"
#include "Camera.h"
#include "collision.h"
#include "CharacterManager.h"
#include "Player.h"

Goal::Goal(class Game * game, D3DXVECTOR2 pos):GameObject(game)
{
	m_pos = pos;
}

void Goal::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/カエル.png");
	pl = game()->GetCm()->GetPlayer();
}

void Goal::Uninit(void)
{
	
}

void Goal::Update(void)
{
	if (HitCheckBox(pl->GetPlayerPos(), PLAYER_SIZE_X, PLAYER_SIZE_Y, m_pos, 100.0f, 100.0f)) {
		flag_goal = true;
		game()->SetGoal(flag_goal);
		//ゴール処理
		/*
			GetStageでステージ情報を取得して
			そのステージのクリアフラグをtrueにする
			Gameのステージを保持しているポインタのステージフラグがtureになったら
			シーン切り替えを行う
		*/
	}
}

void Goal::Draw(void)
{

	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//ブロックの描画
	DrawSpriteColorRotate(m_TextureNo,
		basePos.x + m_pos.x,
		basePos.y + m_pos.y,
		200.0f, 300.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0.0f);
}
