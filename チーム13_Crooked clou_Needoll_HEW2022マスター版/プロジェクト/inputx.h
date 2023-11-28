//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include <XInput.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�{�^���ꗗ

// XINPUT_GAMEPAD_DPAD_UP			�\���L�[��
// XINPUT_GAMEPAD_DPAD_DOWN			�\���L�[��
// XINPUT_GAMEPAD_DPAD_LEFT			�\���L�[��
// XINPUT_GAMEPAD_DPAD_RIGHT		�\���L�[�E
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		L�X�e�B�b�N��������
// XINPUT_GAMEPAD_RIGHT_THUMB		R�X�e�B�b�N��������
// XINPUT_GAMEPAD_LEFT_SHOULDER		L�{�^��
// XINPUT_GAMEPAD_RIGHT_SHOULDER	R�{�^��
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//�X�e�B�b�N�͈̔�
// X�� ��-1.0�@�E 1.0
// Y�� �� 1.0�@��-1.0

enum {
	
	DOWNLEFT,	//����:����
	DOWN,		//����:��
	DOWNRIGHT,	//����:�E��
	RIGHT,		//����:�E
	UPPERRIGHT,	//����:�E��
	UPPER,		//����:��
	UPPERLEFT,	//����:����
	LEFT,		//����:��
	CENTER,		//����:����

	INPUT_MAX,
};

//�g���K�[�͈̔�
// 0 �` 255

// �o�C�u���[�V�����͈̔�
// 0 �` 255

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT X_InitializePad(void);			// �p�b�h������
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
