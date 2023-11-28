//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �t�F�[�h�̏��
enum FADE_STATE
{
	FADE_NONE = 0,	// �t�F�[�h���������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C��������
	FADE_OUT,		// �t�F�[�h�A�E�g������

	FADE_MAX,		// �I�[�R�[�h
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SceneFadeIn(void);//�t�F�[�h�C���̂�
void SceneTransition(void);//�t�F�[�h�A�E�g���Ă���t�F�[�h�C������

FADE_STATE GetFadeState(void);

void SetFadeColor(float r, float g, float b, float a);

float GetColor(void);