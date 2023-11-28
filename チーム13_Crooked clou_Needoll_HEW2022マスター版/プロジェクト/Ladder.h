/*********************************************
 * Ladderヘッダ								 *
 *針が刺さったら上へ上昇するブロックのクラス *
 *										     *
 *         Auther:ウチヤマ					 *
 *         Date  :12/12						 *
 *********************************************/
#pragma once

#include "GameObject.h"

#include "Bullet.h"
class Ladder : public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int use;

	int state;
	BULLET* pBullet = nullptr;

	bool hit_bullet = false;
public:
	Ladder(class Game* game, D3DXVECTOR2 pos);
	~Ladder() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR2 GetPos(void) { return m_pos; }
	bool GetHit(void) { return hit_bullet; }
	void SetHit(bool state) { hit_bullet = state; }
};