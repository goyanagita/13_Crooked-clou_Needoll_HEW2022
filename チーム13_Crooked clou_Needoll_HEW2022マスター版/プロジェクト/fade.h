//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// フェードの状態
enum FADE_STATE
{
	FADE_NONE = 0,	// フェード処理をしていない
	FADE_IN,		// フェードイン処理中
	FADE_OUT,		// フェードアウト処理中

	FADE_MAX,		// 終端コード
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SceneFadeIn(void);//フェードインのみ
void SceneTransition(void);//フェードアウトしてからフェードインする

FADE_STATE GetFadeState(void);

void SetFadeColor(float r, float g, float b, float a);

float GetColor(void);