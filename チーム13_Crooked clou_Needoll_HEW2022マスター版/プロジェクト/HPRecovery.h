#pragma once
/*****************************************
 * HPRecoveryヘッダ						 *
 *HPの回復の管理を行うクラス             *
 *ブロック的なのがあって当たり判定内に   *
 *入るとHPが回復する仕様				 *
 *         Auther:						 *
 *         Date  :						 *
 *****************************************/

#include "GameObject.h"
#include "main.h"

class HPRecovery :public GameObject {
private:
	int m_TextureNo = 0;//テクスチャの識別子
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	D3DXVECTOR2 first_pos;

	int save_flag;
	int use;

	int state;

public:

	HPRecovery(class Game* game, D3DXVECTOR2 pos);
	~HPRecovery() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 GetPos(void) { return m_pos; }
};