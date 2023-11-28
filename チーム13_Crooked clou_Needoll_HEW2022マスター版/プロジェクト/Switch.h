#pragma once

#include "GameObject.h"
#include "main.h"


class SWITCH :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 pos;
	D3DXVECTOR2 vel;
	float rot;
	D3DXVECTOR2 first_pos;
	D3DXVECTOR2 sw_pos;

	int save_flag;
	int fool_flag;
	int use;

	int state;
	class CharacterManager* cm;
	int sw;

public:

	SWITCH(class Game* game);
	~SWITCH() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetSwitch(void) { return pos; }
	enum SWITCH_state
	{
		SWITCH_STATE_AIR,//空中ブロック(理想はSPDマン)
		SWITCH_STATE_GRAND,//地上のブロック
		SWITCH_STATE_GIMIC,//ギミックのブロック(ギミックの処理は別で行う)
		SWITCH_STATE_NONE//何にも当たらなかった
	};
};