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
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/�J�G��.png");
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
		//�S�[������
		/*
			GetStage�ŃX�e�[�W�����擾����
			���̃X�e�[�W�̃N���A�t���O��true�ɂ���
			Game�̃X�e�[�W��ێ����Ă���|�C���^�̃X�e�[�W�t���O��ture�ɂȂ�����
			�V�[���؂�ւ����s��
		*/
	}
}

void Goal::Draw(void)
{

	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//�u���b�N�̕`��
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
