/*****************************************
 * EnemyBulletヘッダ					 *
 *鳥の発射する羽根のクラス        　　　 *
 *										 *
 *         Auther:		ミヤベ		 　　*
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"
#define MAX_BIRDBULLET 2	//弾の表示最大数
#define BULLET_SPEED (4.0f)//弾の速度

class ENEMYBULLET:public GameObject
{
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	int m_TextureF1 = 0;//テクスチャの識別子
	int m_TextureF2 = 0;//テクスチャの識別子

	float		height;	//高さ
	int			m_muki;	//向き

	int			frame;	//有効フレーム
	bool		use;	//可視フラグ
	D3DXVECTOR2 gravity;//重力
	bool        check_eb;  //当たり判定

	class CharacterManager* cm;
	class BLOCK * bl;
	class Enemy_Bird* eb;

	
public:
	ENEMYBULLET(class Game* game);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetEnemyBullet(D3DXVECTOR2 pos, int muki);
	bool GetCheckEB() { return check_eb; }
	void SetCheckEB(bool state) { check_eb = state; }
	bool GetUse(void) { return use; }
	D3DXVECTOR2 GetEbPos(void) { return m_pos; }
	void Delete() { use = false; }

};

