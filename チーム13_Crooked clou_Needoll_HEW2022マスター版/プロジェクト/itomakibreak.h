/*****************************************
 * itomakibreakヘッダ				     *
 *破壊される糸巻きのクラス               *
 *糸巻きがあってプレイヤーは通過できない *
 *が針を当てることで壊れる仕様           *  
 *         Auther:	柳田			 　　*
 *         Date  :						 *
 *****************************************/
#pragma once


#include "GameObject.h"
#include "main.h"
#define ITOMAKIBREAK_NUM		(10)		// エフェクトのMax数

 // バレット構造体
struct EXPLOSION
{
	D3DXMATRIX				mtxWorld;
	bool					use;	// true:使っている  false:未使用
	bool					bloken; // 破壊アニメーション中フラグ
	D3DXVECTOR3				pos;	// バレットの座標
	D3DXVECTOR3				dir;	// バレットの移動方向
	float					speed;	// バレットの移動スピード
	float					frame;	// フレーム数
	int						anmIndex;//アニメーションパターン
	int						anmWait;//パターンの表示ウエイト
};



class ItomakiBreak :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	int m_TextureNo2 = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	float rot = 0.0f;

	int save_flag;
	int use;
	int						anmIndex;//アニメーションパターン
	int						anmWait;//パターンの表示ウエイト
	int state;
	int SENo;

	float	frame;	// フレーム数
	int AnimPtn = 0;
	int AnimCounter;
	bool broken = false;
	

public:

	ItomakiBreak(class Game* game, D3DXVECTOR2 pos);
	~ItomakiBreak() {};
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
private:
	struct DATA {


		int			animePtn;
		int			animeCounter;
		int muki;
	};
	DATA itomakibreak;

};


