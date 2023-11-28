/*********************************************
 * Lifeヘッダ								 *
 *体力のクラス                               *
 *										     *
 *         Auther:ウチヤマ					 *
 *         Date  :12/12						 *
 *********************************************/
#pragma once
#include "GameObject.h"
#include "input.h"
#include "inputx.h"
#include "Bullet.h"
#include "Game.h"
#include "Player.h"

class Life : public GameObject {
private:
	int m_texture_no;
	const int thread_cap_max = MAX_THREAD;
	int thread_cap;
	D3DXVECTOR2 m_pos;
	int view_gauge;
	int life;
public:
	Life(class Game* game);
	~Life() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR2 GetPos(void) { return m_pos; }

};