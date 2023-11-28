/*****************************************
 *AutoBookヘッダ                         *
 *(山下とヘッダ名が被っていたので変更)   *
 *                              ミヤベ   *
 *勝手に倒れる本のクラス((Coming Soon)	 *
 *										 *
 *         Author:山内		　　　		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"
#include "GameObject.h"
#include "Bullet.h"



class AUTOBOOK :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	float rot;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int fool_flag;
	int use;

	int state;
	BULLET* pBullet = nullptr;
	class CharacterManager* cm;
	int sw;

public:

	AUTOBOOK(class Game* game, D3DXVECTOR2 pos);
	~AUTOBOOK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	enum Block_state
	{
		BLOCK_STATE_AIR,//空中ブロック(理想はSPDマン)
		BLOCK_STATE_GRAND,//地上のブロック
		BLOCK_STATE_GIMIC,//ギミックのブロック(ギミックの処理は別で行う)
		BLOCK_STATE_NONE//何にも当たらなかった
	};
};