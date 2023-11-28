/*****************************************
 * Characterヘッダ					     *
 *すべてのキャラクターはこれを継承する   *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "BaseCharacter.h"

#define PLAYER_SIZE_X (32.0f*3)
#define PLAYER_SIZE_Y (32.0f*4.5)
class Character :public GameObject
{
private:
	/*struct Character[8]:BaseCharacter*/
public:
	struct DATA
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 vel;
		int m_TextureNo = 0;//テクスチャの識別子

		float speed = 0;//移動速度
		float speedY = 0;
		float scale = 1;//大きさ
		float wx = 0;//横幅
		float wy = 0;//縦幅
		float vx = 0;//横移動量
		float vy = 0;//縦移動量
		int hp = 0;//体力
		int CharaId;//0…プレイヤ 1以上敵
		int GroupId;//0…味方　1…敵
		float gravityscale;
		float moveinpulse;
		bool fieldstand;
	};

	DATA Chara;
	
	Character(class Game* game);

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Create() {};
	int hp() { return Chara.hp; }
	float speed() { return Chara.speed; }
	float speedY() { return Chara.speedY; }
	int CharaId() { return Chara.CharaId; }
	int GroupId() { return Chara.GroupId; }


};

