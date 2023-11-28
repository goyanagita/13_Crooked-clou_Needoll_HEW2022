#pragma once

#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "texture.h"
#include "camera.h"
#include "GameObject.h"

#define MAP_WIDTH 60
#define MAP_HEIGHT 20
#define MAPCHIP 32.0f

#define NUM_VERTEX 4	//必要な頂点の数

#define DIVIDE_X 8	//横の分割数
#define DIVIDE_Y 8	//縦の分割数

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

class BackGround :public GameObject {
private:
	 int m_texture_no = 0;
	  float g_MapBaseType[8] = {
	0.0f,	//通常の草原
	0.125f,	//深い草原
	0.25f,	//明るい草原
	0.375f,	//暗い草原
	0.5f,	//土
	0.625f,	//荒れ土
	0.75f,	//砂漠
	0.875f,	//道路
	};

	  //==================================
	//1/23に追加
	//==================================

	  const char* bg_stage[5] =
	  {
		"data/TEXTURE/stage1-1.png",//ここを各ステージに変える
		"data/TEXTURE/stage1-2.png",
		"data/TEXTURE/stage1-2.png",
		"data/TEXTURE/stage1-2.png",
		"data/TEXTURE/stage1-2.png"
	  };
	  int stage_num = 0;


	  D3DXVECTOR2 m_pos;

public:

	BackGround(class Game* game);
	HRESULT InitBG(void);
	void UninitBG(void);
	void UpdateBG(void);
	void DrawBG(void);
};