/*****************************************
 *DownBookヘッダ                         *
 *(山内とヘッダ名が被っていたので変更)   *
 *                              ミヤベ   * 
 *本のクラス							 *
 *										 *
 *         Auther:山下		　　　		 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "GameObject.h"
#include "main.h"
#include "Bullet.h"




class DOWNBOOK :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;
	

	bool flag;
	int use;
	float rot;
	float cnt;

	class BULLET* bl = nullptr;

public:

	DOWNBOOK(class Game* game, D3DXVECTOR2 pos);
	~DOWNBOOK() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
};