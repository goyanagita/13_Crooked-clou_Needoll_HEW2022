/*****************************************
 * FloatingGimmickヘッダ			　　 *
 *浮遊ギミックのクラス        　　　 　　*
 *										 *
 *         Auther:		山内		 　　*
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"


#define MAX_GIMMICK 8		//浮遊ギミックの個数
#define RIGHT_END 1500.0f	//浮遊ギミックエリアの右端

	struct GIMMICK
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 vel;
		float rot;
		D3DXVECTOR2 first_pos;

		int save_flag;
		int fool_flag;
		int use;

		int state;
	};
	static GIMMICK g_Gimmick[MAX_GIMMICK];


class FLGIMMICK :public GameObject {
private:

	int m_TextureNo = 0;//テクスチャの識別子
	BULLET* pBullet = nullptr;
	class CharacterManager* cm;
public:

	FLGIMMICK(class Game* game,D3DXVECTOR2 pos);
	~FLGIMMICK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	enum Block_state
	{
		BLOCK_STATE_AIR,//空中ブロック(理想はSPDマン)
		BLOCK_STATE_GRAND,//地上のブロック
		BLOCK_STATE_GIMIC,//ギミックのブロック(ギミックの処理は別で行う)
		BLOCK_STATE_NONE//何にも当たらなかった
	};
};