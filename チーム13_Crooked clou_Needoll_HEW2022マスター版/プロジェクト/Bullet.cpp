#include "Bullet.h"
#include "Game.h"
#include "GameObject.h"
#include "texture.h"
#include "sprite.h"
#include "CharacterManager.h"
#include "Block.h"
#include "collision.h"
#include "BulletCollision.h"
#include "Enemy_Field.h"
#include "Enemy_Bird.h"
#include "Enemy_Bee.h"
#include "ObjectManager.h"
#include "Ladder.h"
#include "Boss.h"
#include "Bridge.h"
#include "sound.h"

static float g_RotateTable[4] =
{
	D3DX_PI,		//下向き(180°回転させる)
	(-D3DX_PI / 2),	//左向き(-90°回転させる)
	(+D3DX_PI / 2),	//右向き(+90°回転させる)
	0.0f,			//上向き
};

//=============================================================================
// コンストラクタ
//=============================================================================
BULLET::BULLET(class Game * game):GameObject(game)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/sting.png");
	SENo = LoadSound((char*)"data/SE/ダメージ.wav");
	use = false;

	rot = 0.0f;
}

//=============================================================================
// 初期化処理
//=============================================================================
void BULLET::Init()
{
	//必要な情報を取得する
	cm = game()->GetCm();

	//宮部追加
	om = game()->GetOm();
	
}
//=============================================================================
// 終了処理
//=============================================================================
void BULLET::Uninit()
{
	StopSoundAll();

}

//=============================================================================
// 更新処理
//=============================================================================
void BULLET::Update()
{
	//必要な情報を取得
	BLOCK * bl[MAX_BLOCK] ;
	Ladder* la[MAX_LADDER];
	Enemy_Field* ef[ENEMY_FIELD_MAX];
	Enemy_Bird* ew[ENEMY_FIELD_MAX];
	Enemy_Bee* es[ENEMY_FIELD_MAX];
	Bridge* br[BRIDGE_POAL];//宮部追加


	BOSS* boss = cm->GetBoss();
	
	for(int i = 0;i < cm->GetEnemyfTotal(); i++)
		ef[i] = cm->GetEnemyField(i);
	for (int i = 0; i < cm->GetEnemywTotal(); i++)
		ew[i] = cm->GetBird(i);
	for (int i = 0; i < cm->GetEnemysTotal(); i++)
		es[i] = cm->GetBee(i);
	for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++)
		bl[i] = game()->GetOm()->GetBlock(i);
	for (int i = 0; i < game()->GetOm()->GetTotalLadder(); i++)
		la[i] = game()->GetOm()->GetLadder(i); 
	for (int i = 0; i < om->GetPoalTotal(); i++)//宮部追加
		br[i] = om->GetBridge(i);

	if (use == true) {
		//弾の座標更新
		if (check != true && hit_field != true && check_ladder != true && hit_boss != true) {
			m_pos += vel;
			if (hit_enemy != true ) {
				vel.y += gravity.y;
				rot += rot_speed;
			}


		}

		//有効フレームを減らす
		frame--;


		//弾とブロックの当たり判定
		for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++) {
			
			
			if (HitCheckBox(m_pos, 64.0f, 86.0f, bl[i]->GetPos(), 50.0f, 50.0f))
			{
				check = true;
			}
		}
		for (int i = 0; i < game()->GetOm()->GetTotalLadder(); i++) {
			if (HitCheckBox(m_pos, 64.0f, 86.0f, la[i]->GetPos(), 50.0f, 50.0f))
			{
				check_ladder = true;
			}
		}

		//敵と弾の当たり判定
		for (int i = 0; i < cm->GetEnemyfTotal(); i++) {//クマ

			if (ef[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, ef[i]->Chara.pos, 85.0f, 115.0f)) {
				ef[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (ef[i]->GetVel())*-1;

				PlaySound(SENo, 0);

			}
		}
		for (int i = 0; i < cm->GetEnemywTotal(); i++) {//鳥

			if (ew[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, ew[i]->Chara.pos, 90.0f, 105.0f)) {
				ew[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (ew[i]->GetVel());

				PlaySound(SENo, 0);


			}
		}
		for (int i = 0; i < cm->GetEnemysTotal(); i++) {//蜂

			if (es[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, es[i]->Chara.pos, 128.0f, 128.0f)) {
				es[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (es[i]->GetVel());

				PlaySound(SENo, 0);


			}
		}

		//宮部追加
		for (int i = 0; i < om->GetPoalTotal(); i++)
		{
			if (i % 2 == 1) {
				if (HitCheckBullet(m_pos, 45.0f, 64.0f, br[i]->GetPos(), 64.0f, 64.0f))
				{
					br[i]->SetHit(true);
					hit_poal = true;
					ch_len = br[i]->GetPos() - br[i - 1]->GetPos();//偶数番目と奇数番目の柱の距離を測る
				}
				if (game()->GetOm()->GetBridge(i)->GetBuildS() ||
					game()->GetOm()->GetBridge(i)->GetBuildL() ||
					GetKeyboardPress(DIK_T) ||
					GetKeyboardPress(DIK_V)) {
					hit_poal = false;//橋完成したらpoalとの当たり判定を無くす
					use = false;
				}
			}
		}
	}
	
	if (m_pos.y > 1200 /*|| m_pos.y  < 800*/ )
		use = false;
}

//=============================================================================
// 描画処理
//=============================================================================
void BULLET::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	if (use == true) {
		DrawSpriteColorRotate(m_TextureNo, basePos.x + m_pos.x, basePos.y + m_pos.y, 64.0f, 64.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_RotateTable[m_muki]+ rot);
	}
	
}

//=============================================================================
// 弾の生成処理
//=============================================================================
void BULLET::SetBullet(D3DXVECTOR2 pos, int muki,float pl_rot)
{
	Character* gp = cm->GetPlayer();
	
	if (use == false) {
		m_pos = pos;
		m_muki = muki;

		switch (m_muki) {
			case 7://左向き
				vel = D3DXVECTOR2(-BULLET_SPEED, -7.0f);
				vel.x += gp->speed();
				vel.y += gp->speedY();
				gravity = D3DXVECTOR2(0.3f, 0.2f);
				rot = +0.75f + pl_rot;
				rot_speed = -0.03f ;
				break;

			case 8://右向き
				vel = D3DXVECTOR2(BULLET_SPEED, -7.0f);
				vel.x += gp->speed();
				vel.y += gp->speedY();
				gravity = D3DXVECTOR2(0.3f, 0.2f);
				rot = -0.75f + pl_rot;
				rot_speed = 0.03f ;
				break;
		}
		height = 0.0f; //後で対応する
		hit_enemy = false;
		hit_field = false;
		hit_boss = false;
		check_ladder = false;

		//有効フレームをセット
		frame = 300;

		//可視フラグオン
		use = true;

		
	}
}

/*

投げモーションで判定をすぐ投げる
ぶつかったらそこで演算を止めて表示する

*/