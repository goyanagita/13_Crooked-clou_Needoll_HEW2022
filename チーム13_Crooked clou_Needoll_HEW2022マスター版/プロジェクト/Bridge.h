#pragma once
/*********************************************
 * Bridgeヘッダ								 *
 *橋を表示するクラス						 *
 *										     *
 *         Author:ミヤベ　　　　　　		 *
 *         Date  :1/08					     *
 *********************************************/

#include "GameObject.h"
#include "input.h"
#include "inputx.h"
#include "Bullet.h"
#include "Game.h"

class Bridge : public GameObject {
private:
	int AnimPtn = 0;
	int AnimCounter;
	int m_TexturePo1 = 0;//テクスチャの識別子
	int m_TextureBr1 = 0;//テクスチャの識別子
	int m_TextureBr2 = 0;//テクスチャの識別子
	int m_SENo;
	D3DXVECTOR2 m_pos;

	BULLET* pBullet = game()->GetBullet();

	float posx;
	int save_flag;
	int use;

	bool build_s = false;
	bool build_l = false;
	int state;
	bool hit;
	
public:
	Bridge(class Game* game, D3DXVECTOR2 pos);
	~Bridge() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetHit(bool bhit) { hit = bhit; }
	bool GetBuildS() { return build_s; }
	bool GetBuildL() { return build_l; }
	int GetAnim() { return AnimPtn; }

	D3DXVECTOR2 GetPos(void) { return m_pos; }

};


/*


1.やりたいこと
橋が刺さったら針を自動で回収する

2.障害が何か
橋が完成したら回収する機構作ったら橋は常に立ち続けているから針は発射されなくなる

3.根本
根本は小さい橋か大きい橋が一個たったら全部当たり判定発生しちゃう











*/