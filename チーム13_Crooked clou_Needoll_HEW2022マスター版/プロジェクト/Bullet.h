/*****************************************
 * Bulletヘッダ					         *
 *プレイヤーの発射する針のクラス         *
 *										 *
 *         Auther:		ウチヤマ		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"

#define MAX_BULLET 1	//弾の表示最大数
#define BULLET_SPEED (6.0f)//弾の速度

class BULLET :public GameObject {
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	int m_TextureNo = 0;//テクスチャの識別子

	float		height;	//高さ
	int			m_muki;	//向き

	int			frame;	//有効フレーム
	int			use;	//可視フラグ
	D3DXVECTOR2 gravity;//重力
	bool        check;  //当たり判定

	bool		check_ladder;
	bool		hit_field = false;//地面との衝突判定
	bool		hit_enemy = false;
	bool		hit_boss = false;

	float rot;			//回転角度
	float rot_speed;	//回転スピード
	class CharacterManager* cm;//キャラクターマネージャーポインタ

		//宮部追加
	class ObjectManager* om;//オブジェクトマネージャーポインタ
	bool        hit_poal = false;//橋の柱との当たり判定
	D3DXVECTOR2 ch_len;
	int			SENo;


public:



	BULLET(class Game* game);
	~BULLET() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetBullet(D3DXVECTOR2 pos, int muki, float pl_rot);//弾のセッター
	//各ゲッター
	bool GetCheck() { return check; }
	bool GetCheckLadder() { return check_ladder; }
	bool GetHitField() { return hit_field; }
	bool GetHitEnemy(void) { return hit_enemy; }
	bool GetUse(void) { return use; }
	float GetFrame() { return frame; }
	float GetRot(void) { return rot; }
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	bool GetHitBoss(void) { return hit_boss; }

	bool GetHit(void) {
		if (GetHitBoss() || GetHitEnemy())
			return true;
		else
			return false;
	}

	//宮部追加
	D3DXVECTOR2 GetLen() { return ch_len; }
	bool GetHitPoal(void) { return hit_poal; }

	//個別のセッター
	void SetCheck(bool state) { check = state; }
	void SetUse(bool state) { use = state; }
	void SetHitField(bool state) { hit_field = state; }
	void SetVelX(void) { vel.x *= -1; /*vel.x /= 2;*/ }
	void SetVelY(void) { vel.y *= -1; /*vel.y /= 2;*/ }
	void SetPos(D3DXVECTOR2 pos) { m_pos += (pos * 10.0f); }
	void SetCheckLadder(bool state) { check_ladder = state; }
	void SetHitBoss(bool hit) { hit_boss = hit; }



};

