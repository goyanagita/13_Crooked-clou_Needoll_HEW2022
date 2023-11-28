#include "BackGround.h"
#include "Game.h"

//�w�i�̕`��ōs��

BackGround::BackGround(class Game * game) :GameObject(game)
{
}

HRESULT BackGround::InitBG(void)
{
	//==================================
	//1/23�ɒǉ�
	//==================================
	stage_num = game()->GetStage();
	m_texture_no = LoadTexture((char*)bg_stage[stage_num]);//�����ς���
	m_pos = D3DXVECTOR2((32 * 210) / 2, (32 * 34) / 2);
	return S_OK;
	return S_OK;
}

void BackGround::UninitBG(void)
{
}

void BackGround::UpdateBG(void)
{
}

void BackGround::DrawBG(void)
{
	//�x�[�X���W���󂯎��
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//�x�[�X���C���[�̕`��

	DrawSprite(m_texture_no,
		basePos.x + m_pos.x, basePos.y + m_pos.y, 32.0f * 210, 32.0f * 34,
		0.0f,
		0.0f,
		1.0f,
		1.0f);
}

