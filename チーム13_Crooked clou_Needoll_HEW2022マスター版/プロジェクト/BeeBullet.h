/*****************************************
 * BeeBulletヘッダ				     	 *
 *蜂が打ち出す弾のクラス　　　　　       *
 *										 *
 *         Auther:	ミヤベ　　　　　	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"
#define MAX_BIRDBULLET 3	//弾の表示最大数
#define BULLET_SPEED (4.0f)//弾の速度

class BEEBULLET:public GameObject
{
	private:
		
		struct DATA
		{
			D3DXVECTOR2 m_pos;
			D3DXVECTOR2 vel;
			int m_TextureS1 = 0;//テクスチャの識別子
			int m_TextureS2 = 0;//テクスチャの識別子

			float		height;	//高さ
			int			m_muki;	//向き

			int			frame;	//有効フレーム
			bool		use;	//可視フラグ
			D3DXVECTOR2 gravity;//重力
			bool        check_eb;  //当たり判定
		};
	
		DATA bbullet;

		class CharacterManager* cm;

	public:
		BEEBULLET(class Game* game);
		void Init();
		void Uninit();
		void Update();
		void Draw();
		void SetBeeBullet(D3DXVECTOR2 pos, int muki);
		bool GetCheckBB() { return bbullet.check_eb; }
		void SetCheckBB(bool state) { bbullet.check_eb = state; }
		bool GetUse() { return bbullet.use; }
		D3DXVECTOR2 GetBbPos(void) { return bbullet.m_pos; }
		void Delete() { bbullet.use = false; }

};

