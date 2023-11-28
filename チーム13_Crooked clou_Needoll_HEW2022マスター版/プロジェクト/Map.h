/*****************************************
 * Mapヘッダ							 *
 * マップの管理を行うクラス		         *
 *										 *
 *         Auther:	ウチヤマ			 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"
#include "renderer.h"
#include "GameObject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAX_MAPDATA 6

#define MAX_YMAP 34
#define MAX_XMAP 210

#define FIELD_SIZE 32.0f

class MAP: public GameObject
{
private:
	bool error_flag = false;

	const char* fname[5] =
	{
		"data/MAP/Stage1.txt",//Stage1
		"data/MAP/Stage2.txt",//Stage2
		"data/MAP/Stage3.txt",//Stage3
		"data/MAP/Stage4.txt",//Stage4
		"data/MAP/Stage5.txt",//Stage5
	};

	int m_stage = 0;
	int m_BGMNo;	//BGM識別子
	int SENo;

public:
	struct DATA
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 collipos;
		int mesh;
		int use;
		int i = 0;
		D3DXVECTOR2 brpos;//宮部追加
	};

	bool boss_flag = false;

	DATA m_Mesh[MAX_YMAP][MAX_XMAP];
	MAP(class Game* game,int stage);
	~MAP() {};
	void InitMap(void);
	void UninitMap(void);
	void UpdateMap(void);
	void DrawMap(void);
	bool GetError(void) { return error_flag; }
	bool GetBossFlag(void) { return boss_flag; }
	DATA GetMap(void) { return m_Mesh[0][0]; }

	D3DXVECTOR2 GetMeshColliPos(int x, int y);
};



