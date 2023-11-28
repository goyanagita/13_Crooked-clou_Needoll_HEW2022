/*****************************************
 * Blockヘッダ						     *
 *ターザンブロックのクラス               *
 *										 *
 *         Auther:		ミヤベ			 *
 *         SpecialThanks:アベノリヤス    *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"




class BLOCK :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int use;
	bool hit_bullet = false;
	int state;
	BULLET* pBullet = nullptr;
	
public:
	
	BLOCK(class Game* game,D3DXVECTOR2 pos);//自動的に呼ばれる
	~BLOCK() {};//自動的に呼ばれる
	void Init(void)   ;
	void Uninit(void) ;
	void Update(void) ;
	void Draw(void) ;
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	enum Block_state
	{
		BLOCK_STATE_AIR,//空中ブロック(理想はSPDマン)
		BLOCK_STATE_GRAND,//地上のブロック
		BLOCK_STATE_GIMIC,//ギミックのブロック(ギミックの処理は別で行う)
		BLOCK_STATE_NONE//何にも当たらなかった
	};
	void Hitbullet(bool state) { hit_bullet = state; }
	bool GetHit(void) { return hit_bullet; }
};
