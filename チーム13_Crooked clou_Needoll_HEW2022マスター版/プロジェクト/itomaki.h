#pragma once


#include "GameObject.h"
#include "main.h"


class ITOMAKI :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	 float rot = 1.0f;

	int save_flag;
	int use;

	int state;

	bool broken = false;

public:

	ITOMAKI(class Game* game,D3DXVECTOR2 pos);
	~ITOMAKI() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	//enum Block_state
	//{
	//	BLOCK_STATE_AIR,//空中ブロック(理想はSPDマン)
	//	BLOCK_STATE_GRAND,//地上のブロック
	//	BLOCK_STATE_GIMIC,//ギミックのブロック(ギミックの処理は別で行う)
	//	BLOCK_STATE_NONE//何にも当たらなかった
	//};
};