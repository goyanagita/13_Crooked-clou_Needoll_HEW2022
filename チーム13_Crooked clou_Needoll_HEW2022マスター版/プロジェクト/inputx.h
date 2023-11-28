//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include <XInput.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//ボタン一覧

// XINPUT_GAMEPAD_DPAD_UP			十字キー上
// XINPUT_GAMEPAD_DPAD_DOWN			十字キー下
// XINPUT_GAMEPAD_DPAD_LEFT			十字キー左
// XINPUT_GAMEPAD_DPAD_RIGHT		十字キー右
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		Lスティック押し込み
// XINPUT_GAMEPAD_RIGHT_THUMB		Rスティック押し込み
// XINPUT_GAMEPAD_LEFT_SHOULDER		Lボタン
// XINPUT_GAMEPAD_RIGHT_SHOULDER	Rボタン
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//スティックの範囲
// X軸 左-1.0　右 1.0
// Y軸 上 1.0　下-1.0

enum {
	
	DOWNLEFT,	//入力:左下
	DOWN,		//入力:下
	DOWNRIGHT,	//入力:右下
	RIGHT,		//入力:右
	UPPERRIGHT,	//入力:右上
	UPPER,		//入力:上
	UPPERLEFT,	//入力:左上
	LEFT,		//入力:左
	CENTER,		//入力:無し

	INPUT_MAX,
};

//トリガーの範囲
// 0 ～ 255

// バイブレーションの範囲
// 0 ～ 255

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT X_InitializePad(void);			// パッド初期化
void X_UpdatePad(void);
void X_UninitPad(void);

HRESULT X_InitInput(HINSTANCE hInst, HWND hWnd);
void X_UninitInput(void);
void X_UpdateInput(void);

float X_GetThumbLeftX(int padNo);
float X_GetThumbLeftY(int padNo);
float X_GetThumbRightX(int padNo);
float X_GetThumbRightY(int padNo);

void X_SetLeftVibration(int padNo, int speed);
void X_SetRightVibration(int padNo, int speed);
void X_SetVibration(int padNo, int speed);
void X_StopVibration(int padNo);

int X_GetLeftTrigger(int padNo);
int X_GetRightTrigger(int padNo);

BOOL X_IsButtonPressed(int padNo,DWORD button);
BOOL X_IsButtonTriggered(int padNo,DWORD button);

bool X_RotateRThumbRight(int padNo);
