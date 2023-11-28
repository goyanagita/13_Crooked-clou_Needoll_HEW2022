//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"�|���S���̕`��"			// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
#include "main.h"
#include <time.h>
#include "renderer.h"
#include"fade.h"
#include "sprite.h"
#include "camera.h"
#include "sound.h"
#include "SceneManager.h"
#include "input.h"
#include "inputx.h"
#include <crtdbg.h>


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
//void ChangeScene(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p

#endif

//static SCENE g_Scene;		//�V�[������
//static SCENE g_SceneNext;	//�J�ڐ�̃V�[��

SceneManager scene_mgr;//�V�[���}�l�[�W���[

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	//�����_���V�[�h�̏�����
	srand((unsigned int)time(NULL));

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	InitSound(hWnd);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// �X�V����
				if (scene_mgr.GetErrorFlag() == true || scene_mgr.GetExitFlag() == true)
					break;
				Draw();				// �`�揈��
				

				////�J�ڐ�V�[�����ݒ肳��Ă�����
				//if (g_Scene != g_SceneNext)
				//{
				//	//�V�[���̐؂�ւ����s��
				//	//ChangeScene();
				//}


				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �I������
	Uninit();

	UninitSound();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	X_InitInput(hInstance, hWnd);
	//// �T�E���h�̏�����
	//InitSound(hWnd);

	// �X�v���C�g�����̏�����
	InitSprite();



	// �t�F�[�h�̏�����
	InitFade();

	scene_mgr.Init();

	////�����V�[���Ƃ��ă^�C�g����ʂ��Z�b�g
	//g_Scene = g_SceneNext = SCENE_NONE;

	//SceneFadeIn(SCENE_GAME);

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �t�F�[�h�̉������
//	UninitFade();
	scene_mgr.Uninit();
	// �X�v���C�g�����̉��
	UninitSprite();

	// �e�N�X�`���̉��
	UninitTexture();

	//// �T�E���h�̏I������
	//UninitSound();

	//// ���͏����̏I������

	X_UninitInput();
	UninitInput();

	// �����_�����O�̏I������
	UninitRenderer();
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{

	//// ���͏����̍X�V����
	UpdateInput();
	X_UpdateInput();

	//�t�F�[�h�̍X�V����
	UpdateFade();
	
	scene_mgr.Upadate();
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);
	

	////���ݓ��삵�Ă���V�[����`�悷��
	//switch (g_Scene)
	//{
	//case SCENE_NONE:
	//	break;
	//case SCENE_TITLE:
	//	DrawTitle();
	//	break;
	//case SCENE_GAME:
	//	DrawGame();
	//	break;
	//}

	scene_mgr.Draw();

	//�t�F�[�h�̍X�V����
	DrawFade();


	
	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}




