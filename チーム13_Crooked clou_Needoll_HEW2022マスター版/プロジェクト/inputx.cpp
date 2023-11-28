//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEADZONE			8800	// �e����25%�𖳌��]�[���Ƃ���
#define MAX_CONTROLLERS     4

struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitializePad(void);			// �p�b�h������
void UpdatePad(void);
void UninitPad(void);
void X_ThumbRightNow(int padNo);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];
static float	g_LeftStickX[MAX_CONTROLLERS];
static float	g_LeftStickY[MAX_CONTROLLERS];
static float	g_RightStickX[MAX_CONTROLLERS];
static float	g_RightStickY[MAX_CONTROLLERS];

static int		g_RotateNow = CENTER;
static int		g_RotateOld;


//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT X_InitInput(HINSTANCE hInst, HWND hWnd)
{	
	// �p�b�h�̏�����
	X_InitializePad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void X_UninitInput(void)
{
	// �p�b�h�̏I������
	X_UninitPad();
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void X_UpdateInput(void)
{
	// �p�b�h�̍X�V
	X_UpdatePad();

	X_ThumbRightNow(0);

}

//---------------------------------------- ������
HRESULT X_InitializePad(void)			// �p�b�h������
{
	//������
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);
		
	return true;

}

//------------------------------------------- �I������
void X_UninitPad(void)
{
	//�p�����[�^�̃��Z�b�g
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//�o�C�u���[�V������~
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ �X�V
void X_UpdatePad(void)
{
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//����FERROR_SUCCESS�@0
		//�ڑ������FERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//�g���K�[�쐬
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//���X�e�B�b�N���̍쐬
		float LX = g_Controllers[i].state.Gamepad.sThumbLX;
		float LY = g_Controllers[i].state.Gamepad.sThumbLY;

		float magnitude = sqrtf((LX * LX) + (LY * LY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			g_Controllers[i].state.Gamepad.sThumbLX = 0;
			g_Controllers[i].state.Gamepad.sThumbLY = 0;
		}

		if(g_Controllers[i].state.Gamepad.sThumbLX >= 0)
			g_LeftStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbLX / 32767;
		else
			g_LeftStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbLX / 32768;

		if (g_Controllers[i].state.Gamepad.sThumbLY >= 0)
			g_LeftStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbLY / 32767;
		else
			g_LeftStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbLY / 32768;

		//�E�X�e�B�b�N���̍쐬
		float RX = g_Controllers[i].state.Gamepad.sThumbRX;
		float RY = g_Controllers[i].state.Gamepad.sThumbRY;

		magnitude = sqrtf((RX * RX) + (RY * RY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			g_Controllers[i].state.Gamepad.sThumbRX = 0;
			g_Controllers[i].state.Gamepad.sThumbRY = 0;
		}

		if (g_Controllers[i].state.Gamepad.sThumbRX >= 0)
			g_RightStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbRX / 32767;
		else
			g_RightStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbRX / 32768;

		if (g_Controllers[i].state.Gamepad.sThumbLY >= 0)
			g_RightStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbRY / 32767;
		else
			g_RightStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbRY / 32768;
	}
}

//�X�e�B�b�N�͈̔�
// X ��-1.0�@�E 1.0
// Y �� 1.0�@��-1.0
float X_GetThumbLeftX(int padNo)
{
	return g_LeftStickX[padNo];
}

float X_GetThumbLeftY(int padNo)
{
	return g_LeftStickY[padNo];
}

float X_GetThumbRightX(int padNo)
{
	return g_RightStickX[padNo];
}

float X_GetThumbRightY(int padNo)
{
	return g_RightStickY[padNo];
}

//�g���K�[�͈̔�
// 0 �` 255
int X_GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int X_GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// �o�C�u���[�V�����͈̔�
// 0 �` 255
void X_SetLeftVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}

void X_SetRightVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void X_SetVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void X_StopVibration(int padNo)
{
	g_Controllers[padNo].vibration.wLeftMotorSpeed = 0;
	g_Controllers[padNo].vibration.wRightMotorSpeed = 0;
}

//�{�^��������Ԃ̎擾
BOOL X_IsButtonPressed(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].state.Gamepad.wButtons);
}

//�{�^���p���X��Ԃ̎擾
BOOL X_IsButtonTriggered(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].trigger.Gamepad.wButtons);
}

void X_ThumbRightNow(int padNo) {
	g_RotateOld = g_RotateNow;

	if ((X_GetThumbRightX(padNo) == 0) && (X_GetThumbRightY(padNo) == 0)) {
		g_RotateNow = CENTER;
	}

	if (X_GetThumbRightX(padNo) > 0) {
		g_RotateNow = RIGHT;
	}
	if (X_GetThumbRightX(padNo) < 0) {
		g_RotateNow = LEFT;
	}
	if (X_GetThumbRightY(padNo) > 0) {
		g_RotateNow = UPPER;
	}
	if (X_GetThumbRightY(padNo) < 0) {
		g_RotateNow = DOWN;
	}

	if ((X_GetThumbRightX(padNo) > 0) && (X_GetThumbRightY(padNo) > 0)) {
		g_RotateNow = UPPERRIGHT;
	}
	if ((X_GetThumbRightX(padNo) < 0) && (X_GetThumbRightY(padNo) > 0)) {
		g_RotateNow = UPPERLEFT;
	}
	if ((X_GetThumbRightX(padNo) > 0) && (X_GetThumbRightY(padNo) < 0)) {
		g_RotateNow = DOWNRIGHT;
	}
	if ((X_GetThumbRightX(padNo) < 0) && (X_GetThumbRightY(padNo) < 0)) {
		g_RotateNow = DOWNLEFT;
	}

}

bool X_RotateRThumbRight(int padNo) {

	if (g_RotateNow == CENTER)
		return false;
	if (g_RotateNow != g_RotateOld) {

		if (g_RotateOld == DOWNLEFT){
			if (g_RotateNow == LEFT) 
				return false;
		}

		if (g_RotateNow > g_RotateOld) {
			return true;
		}
		if (g_RotateOld == LEFT) {
			if (g_RotateNow == DOWNLEFT)
				return true;
		}

		return false;
	}
	return false;
}