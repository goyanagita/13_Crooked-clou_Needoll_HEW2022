#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "CharacterManager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CAMERA_2D::CAMERA_2D(class Game * game):GameObject(game)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CAMERA_2D::Init(void)
{
	
	pos = D3DXVECTOR2(0.0f, 0.0f);
	Base = D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void CAMERA_2D::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CAMERA_2D::Update(void)
{
	Base = (pos * -1);
}

//=============================================================================
// 描画処理
//=============================================================================
void CAMERA_2D::Draw(void)
{
}

//=============================================================================
// カメラのゲッター
//=============================================================================
D3DXVECTOR2 CAMERA_2D::GetBase(void)
{
	return Base;
}
