/*****************************************
 * ThreadGaugeヘッダ					 *
 *糸の消費の管理を行うクラス             *
 *										 *
 *         Auther:	ウチヤマ			 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"

#define USE_BRIDGE	20.0f
#define USE_ENEMY	10.0f
#define USE_TARZAN	5.0f
#define USE_OBJECT	5.0f

#define MAX_THREAD 100







class ThreadGauge :public GameObject {
private:
	int m_texture_no;
	const int thread_cap_max = MAX_THREAD;
	int thread_cap;
	D3DXVECTOR2 m_pos;
	int view_gauge;
public:
	ThreadGauge(class Game* game);
	~ThreadGauge() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UseThread(int use) { thread_cap -= use; };


};