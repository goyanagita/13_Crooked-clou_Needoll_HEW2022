/*****************************************
 * Cameraヘッダ					         *
 *プレイヤーを追従するカメラのクラス     *
 *										 *
 *         Auther:						 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"
#include "renderer.h"
#include "GameObject.h"

class CAMERA_2D:public GameObject {
private:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 player_pos;
	D3DXVECTOR2 Base;
public:
	CAMERA_2D(class Game*game);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetBase(void);
	D3DXVECTOR2 GetPos(void) { return pos; };
	void SetPosX(float x) { pos.x = x; }
	void SetPosY(float y) { pos.y = y; }

};
