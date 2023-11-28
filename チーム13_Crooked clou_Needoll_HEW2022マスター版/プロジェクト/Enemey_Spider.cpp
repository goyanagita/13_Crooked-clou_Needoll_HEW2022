#include "collision.h"
#include "texture.h"
#include "sprite.h"
#include"Enemey_Spider.h"
#include"Player.h"
#include"Camera.h"
#include"CharacterManager.h"
#include "GameObject.h"
#include"Enemy_Field.h"
#include"Map.h"
#include"Player.h"
#include "Map.h"
#include "collision.h"
#include "Fieldcollision.h"
#include "sprite.h"
#include "texture.h"
#include "Game.h"




//**************************************************************
//マクロ定義
//**************************************************************
#define ENEMY_DIVIDE_X 4	//横の分割数
#define ENEMY_DIVIDE_Y 1	//縦の分割数

#define ENEMY_PATTERN_WIDTH		(1.0f / ENEMY_DIVIDE_X)
#define ENEMY_PATTERN_HEIGHT	(1.0f / ENEMY_DIVIDE_Y)

#define SPIDER_RANGE_X	10
#define SPIDER_RANGE_Y	10



//**************************************************************
//プロトタイプ宣言
//**************************************************************


//**************************************************************
//グローバル変数宣言
//**************************************************************
//static Spider*			g_Spider[20];
//static int				g_SpiderCount;

static int g_TextureTs = 0;



//==============================================================
//
//==============================================================
bool Enemy::Collision(D3DXVECTOR2 pos)
{
	if (HitCheckBox(pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, Chara.pos, Chara.wx, Chara.wy)) {
		return true;
	}

	return false;
}

Spider::Spider(class Game * game, D3DXVECTOR2 pos) :Enemy(game)
{
	Chara.pos = pos;
	spider.posStart = pos.y;
	spider.posSpawn = pos.y + 64.0f * 4;
}

//==============================================================
//
//==============================================================
void Spider::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/spider.png");
	
	Chara.vel = D3DXVECTOR2(0.0f, 0.0f);

	Chara.wx = 1.0f;
	Chara.wy = 1.0f;

	Chara.hp = 1;

	//Chara.CharaId以下設定したければここで

	enemy.useFg = true;
	enemy.status = STS_NULL;

	
}

void Spider::Uninit()
{
}

void Spider::Update()
{
	if (enemy.useFg) {
		Player* pPlayer = game()->GetCm()->GetPlayer();
		D3DXVECTOR2 PlayerPos = pPlayer->GetPlayerPos();

		
		if (enemy.useFg == true) {

			switch (enemy.status) {
			case STS_NULL:
				Update_Null(PlayerPos);
				break;


			case STS_SPAWN:
				Update_Spawn(PlayerPos);
				break;


			case STS_NORMAL:
				Update_Back(PlayerPos);
				break;
			}
		}
	
	}
}

void Spider::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();


		DrawSpriteColor(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			50.0f, 150.0f,
			0.0f,
			0.0f,
			ENEMY_PATTERN_WIDTH,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//}
	//if (enemy.useFg) {
	//	//ベース座標を受け取る
	//	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//	//頂点バッファ更新
	//	for (int i = 0; i < g_SpiderCount; i++) {

	//		if (g_Spider[i]->GetUse()) {
	//			D3DXVECTOR2 EnemyPos = g_Spider[i]->GetPos();

	//			DrawSprite(Chara.m_TextureNo, basePos.x + Chara.pos.x, basePos.y + Chara.pos.y, Chara.wx, Chara.wy,
	//				0.0f, 0.0f, ENEMY_PATTERN_WIDTH, ENEMY_PATTERN_HEIGHT);
	//		}
	//	}
	
}

void Spider::Update_Null(D3DXVECTOR2 PlayerPos)
{
	if (HitCheckBox(PlayerPos, PLAYER_SIZE_X, PLAYER_SIZE_Y, D3DXVECTOR2(Chara.pos.x, Chara.pos.y + FIELD_SIZE / 2 + FIELD_SIZE * (SPIDER_RANGE_Y / 2)),
		FIELD_SIZE * SPIDER_RANGE_X, FIELD_SIZE * SPIDER_RANGE_Y)) {
		ChangeStatus(STS_SPAWN);
	}

}

void Spider::Update_Spawn(D3DXVECTOR2 PlayerPos)
{
	Chara.pos.y += 0.5f;
	if (Chara.pos.y >= spider.posSpawn) {
		Chara.pos.y = spider.posSpawn;
	}

	if (!HitCheckBox(PlayerPos, PLAYER_SIZE_X, PLAYER_SIZE_Y, D3DXVECTOR2(Chara.pos.x, Chara.pos.y + FIELD_SIZE / 2 + FIELD_SIZE * (SPIDER_RANGE_Y / 2)), 
		FIELD_SIZE * SPIDER_RANGE_X, FIELD_SIZE * SPIDER_RANGE_Y)) {
		ChangeStatus(STS_NORMAL);
	}
}

void Spider::Update_Back(D3DXVECTOR2 PlayerPos)
{
	Chara.pos.y -= 0.5f;
	if (Chara.pos.y <= spider.posStart) {
		Chara.pos.y = spider.posStart;
		ChangeStatus(STS_NULL);
	}

	if (HitCheckBox(PlayerPos, PLAYER_SIZE_X, PLAYER_SIZE_Y, D3DXVECTOR2(Chara.pos.x, Chara.pos.y + FIELD_SIZE / 2 + FIELD_SIZE * (SPIDER_RANGE_Y / 2)),
		FIELD_SIZE * SPIDER_RANGE_X, FIELD_SIZE * SPIDER_RANGE_Y)) {
		ChangeStatus(STS_SPAWN);
	}
}


