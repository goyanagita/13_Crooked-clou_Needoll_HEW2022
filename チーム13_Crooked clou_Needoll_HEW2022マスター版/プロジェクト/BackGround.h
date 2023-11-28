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

#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�

#define DIVIDE_X 8	//���̕�����
#define DIVIDE_Y 8	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

class BackGround :public GameObject {
private:
	 int m_texture_no = 0;
	  float g_MapBaseType[8] = {
	0.0f,	//�ʏ�̑���
	0.125f,	//�[������
	0.25f,	//���邢����
	0.375f,	//�Â�����
	0.5f,	//�y
	0.625f,	//�r��y
	0.75f,	//����
	0.875f,	//���H
	};

	  //==================================
	//1/23�ɒǉ�
	//==================================

	  const char* bg_stage[5] =
	  {
		"data/TEXTURE/stage1-1.png",//�������e�X�e�[�W�ɕς���
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