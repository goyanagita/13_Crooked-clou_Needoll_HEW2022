#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "Bullet.h"
#include "CharacterManager.h"

#include "Block.h"
#include "collision.h"
#include "ObjectManager.h"
#include "ThreadGauge.h"
#include "Enemy_Field.h"
#include "Ladder.h"
#include "Fieldcollision.h"
#include "Boss.h"
#include "Enemy_Bee.h"
#include "Enemy_Bird.h"
#include "Bridge.h"
#include "sound.h"

static float g_AnimeTable[8] =
{
	0.0f,
	0.125f,
	0.25f,
	0.375f,
	0.5f,
	0.625f,
	0.75f,
	0.875f,

};

static float g_PatternTable[24] =
{
	0.0f,					//null		0
	0.0f,					//L向き		1
	PATTERN_HEIGHT,			//R向き		2
	PATTERN_HEIGHT * 20.0f,	//L歩1列目  3
	PATTERN_HEIGHT * 22.0f,	//R歩1列目  4
	PATTERN_HEIGHT * 21.0f,	//L歩針無し 5
	PATTERN_HEIGHT * 23.0f,	//R歩針無し 6
	PATTERN_HEIGHT * 12.0f,	//L針投げ	7
	PATTERN_HEIGHT * 11.0f,	//R針投げ	8
	PATTERN_HEIGHT * 4.0f,	//Lダメージ	9
	PATTERN_HEIGHT * 5.0f,	//Rダメージ	10

	0.0f,					//11
	0.0f,					//12
	0.0f,					//13
	0.0f,					//14
	0.0f,					//15
	0.0f,					//16
	0.0f,					//17
	0.0f,					//18
	0.0f,					//19
	0.0f,					//20
	0.0f,					//21
	0.0f,					//22
	0.0f,					//23
};

float pos_jump = 0.0f;
bool a = false;
float g_move = 0.0f;

//===================================================================
// 初期化処理
//===================================================================

void Player::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/メインキャラ_チップ(修正）.png");
	m_SENo = LoadSound((char*)"data/SE/throw.wav");
	m_SENo2 = LoadSound((char*)"data/SE/足音.wav");
	Chara.vel = D3DXVECTOR2(0.0f, 0.0f);
	player.animePtn = 0;
	player.animeCounter = 0;
	player.survFlag = 1;
	player.pendulum = 0.0f;
	player.pattern = 1;
	Chara.hp = 3;

	player.flag_throw = false;
	Chara.speed = 0.0f;
	Chara.speedY = 0.0f;


	player.state = PLAY_NUM;
	player.gravity_fall = 0.3f;


	//必要な情報を取得する
	cm = game()->GetCm();
	bl = game()->GetBullet();
	tg = game()->GetTg();
	ladder[0] = game()->GetOm()->GetLadder(0);

	player.survFlag = true;

	//宮部追加
	om = game()->GetOm();
}

//===================================================================
// 終了処理
//===================================================================
void Player::Uninit()
{
	StopSoundAll();

}

//===================================================================
// 更新処理
//===================================================================
void Player::Update()
{
	//座標の更新
	Chara.pos += Chara.vel;
	Chara.vel.x = 0.0f;

	//投げ状態じゃなければ移動可
	if (player.flag_throw != true) {

		if (player.walk && Chara.fieldstand) {
			player.walk_sound_frame++;
			//歩く音
			if (player.walk_sound_frame >= 60) {
				PlaySound(m_SENo2, 0);
				player.walk_sound_frame = 0;
			}

		}	

		MovePlayer();
	}

	//投げ状態移行処理()
	if (player.flag_throw == false && (GetKeyboardTrigger(DIK_K) || X_GetRightTrigger(0))) {
		//左向き
		if (GetPatternL()) {
			player.pattern = 7;
			player.animePtn = 0;
		}
		//右向き
		else if (GetPatternR()) {
			player.pattern = 8;
			player.animePtn = 0;
		}
		player.flag_throw = true;
	}

	//投げ待機状態で右入力されたとき
	if ((GetKeyboardPress(DIK_D) || X_GetThumbLeftX(0) > 0) && player.flag_throw == true) {
		if (Chara.speed <= 6.0f) {
			Chara.speed += 0.1f;
			if (player.pattern == 7) {
				//左向いてるとき
				Chara.speedY -= 0.1f;
				if (player.rot <= 0.75f)
					player.rot += 0.01f;
			}
			else if (player.pattern == 8) {
				//右向いているとき
				Chara.speedY += 0.05f;
				if (player.rot <= 0.5f)
					player.rot += 0.01f;
			}
		}
	}

	//投げ待機状態で左入力されたとき
	if ((GetKeyboardPress(DIK_A) || X_GetThumbLeftX(0) < 0) && player.flag_throw == true) {
		if (Chara.speed >= -6.0f) {
			Chara.speed -= 0.1f;

			if (player.pattern == 7) {
				//左向いているとき
				Chara.speedY += 0.05f;
				if (player.rot >= -0.5f)
					player.rot -= 0.01f;

			}
			else if (player.pattern == 8) {
				//右向いているとき
				Chara.speedY -= 0.1f;
				if (player.rot >= -0.75f)
					player.rot -= 0.01f;
			}
		}
	}

	//針が地面に刺さっているときだけ針とプレイヤーの距離を計算
	if (bl->GetHitField() == true) {
		dir_bullet = Chara.pos - bl->GetPos();
		D3DXVec2Normalize(&dir_bullet, &dir_bullet);

	}

	//針が刺さっているときだけ
		//針の回収
	if ((GetKeyboardPress(DIK_O) || X_RotateRThumbRight(0)) && bl->GetUse() == true && bl->GetHit() != true && bl->GetHitPoal() == false) {
		bl->SetPos(dir_bullet);

	}
	
	//針の方にダッシュ
	if (bl->GetHitField() == true && bl->GetUse() == true) {
		if ((GetPatternR() && X_GetLeftTrigger(0) < 0) || (GetPatternL() && X_GetThumbRightX(0) > 0)) {
			player.thread_dash = true;
			if (player.thread_dash_cnt++ >= 300)
				player.thread_dash_cnt = 300;
		}
	}
	if (player.thread_dash) {
		if ((GetPatternR() && X_GetLeftTrigger(0)) || (GetPatternL() && X_GetThumbRightX(0) <= 0)) {
			if (player.thread_dash_cnt >= 0)
				player.thread_dash_cnt--;
			if (player.thread_dash_cnt <= 0) {
				player.thread_dash_cnt = 0;
				player.thread_dash = false;
			}
		}

	}

	//宮部追加
	for (int i = 0; i < om->GetPoalTotal(); i++) {
		if (game()->GetOm()->GetBridge(i)->GetBuildS() ||
			game()->GetOm()->GetBridge(i)->GetBuildL()) {
			bl->SetUse(false);
		}
	}

	//=================================
	//敵と当たったときにアニメーション
	//=================================
	if (player.hit_anime == false && player.hit_enemy == true) {
		if (GetPatternR())
			player.pattern = 10;
		if (GetPatternL())
			player.pattern = 9;
		player.hit_anime = true;
		player.animePtn = 0;
	}
	Anime();

	//投げる処理
	AttackSting();

	//プレイヤーと針の衝突判定
	HitBullet();

	//死亡処理
	if (Chara.pos.y >= 1200) {
		Chara.hp = 0;
	}
	if (Chara.hp <= 0) {
		player.survFlag = false;
	}
}

//===================================================================
// 描画処理
//===================================================================
void Player::Draw()
{
	//ベース座標を受け取る
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//キャラクターの描画
	DrawSpriteColorRotate(Chara.m_TextureNo,
		basePos.x + Chara.pos.x,
		basePos.y + Chara.pos.y,
		PLAYER_SIZE_X, PLAYER_SIZE_Y,
		g_AnimeTable[player.animePtn],
		g_PatternTable[player.pattern] + 0.001f,
		PATTERN_WIDTH,
		PATTERN_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0.0f);

}

//=============================================================================
//移動系処理
//=============================================================================
void Player::MovePlayer()
{
	player.walk = false;
	player.pos_old.x = Chara.pos.x;//移動する前に現在座標を移動前の座標に保存しておく

	//重力での落下処理
	if (Chara.fieldstand == false && player.jumpFlag == false && bl->GetCheckLadder() != true) {
		Chara.vel.y += player.gravity_fall;
	}
	//着地した処理
	if (Chara.fieldstand == true) {
		player.gravity_fall = 0.0f;
		Chara.vel.y = 0.0f;
	}
	else {
		player.gravity_fall = 0.3f;
	}
	Chara.fieldstand = false;



	//==========================================
	//投げモーション、敵との衝突がなければ歩ける
	//==========================================
	if (!player.flag_throw && player.hit_anime == false) {
		//左方向への移動
		if (GetKeyboardPress(DIK_A) || X_GetThumbLeftX(0) < 0)
		{
			player.walk = true;
			if (player.pattern != 5)
				player.pattern = 3;
			Chara.vel.x = -4.0f;

			if (player.tarzan == false)
				a = true;

		}

		//右方向への移動
		if (GetKeyboardPress(DIK_D) || X_GetThumbLeftX(0) > 0)
		{
			player.walk = true;
			if (player.tarzan == false)
				a = false;
			Chara.vel.x = 4.0f;

			if (player.pattern != 6)
				player.pattern = 4;

		}

		//==========================================
		//歩きをやめた時にアニメーションを待機にする
		//==========================================
		if (player.walk != true) {
			if (player.pattern == 3) {
				player.pattern = 1;
				player.animePtn = 0;
			}
			if (player.pattern == 4) {
				player.pattern = 2;
				player.animePtn = 0;
			}

			StopSound(m_SENo2);
			player.walk_sound_frame = 60;
		}
	}


	//ジャンプ処理(ジャンプ中ではない状態でスペースキーが押されたとき)
	if ((GetKeyboardTrigger(DIK_SPACE) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) && (player.jumpFlag == false) && player.tarzan == false)
	{

		JumpSet();
	}

	//ジャンプ中の処理
	if (player.jumpFlag == true)
	{
		//高さの更新
		player.height += player.jumpPower;

		//高さの更新(位置)
		Chara.pos.y -= player.jumpPower;

		//ジャンプ力の減衰
		player.jumpPower -= player.gravity;

		//地面に着地した場合
		if (Chara.fieldstand == true)
		{
			//高さを0に戻してジャンプ中フラグを落とす
			player.height = 0.0f;
			if (!player.tarzan)
				Chara.pos.y = pos_jump;
			player.jumpFlag = false;

		}
	}

	//ターザンの処理
	if (bl->GetCheck() == true)
	{
		player.tarzan = true;

		BLOCK* pBlock[MAX_BLOCK];
		for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++) {
			pBlock[i] = game()->GetOm()->GetBlock(i);

			if (pBlock[i]->GetHit() == false)
				continue;

			player.pdir = Chara.pos - pBlock[i]->GetPos();

			D3DXVECTOR2 vDif;
			vDif = pBlock[i]->GetPos() - Chara.pos;//プレイヤーからブロックの方に向くベクトル
			float len = D3DXVec2Length(&vDif);
			D3DXVec2Normalize(&vDif, &vDif);//2個目の引数を正規化して一つ目にぶち込む
			D3DXVec2Normalize(&player.pdir, &player.pdir);//2個目の引数を正規化(1.0のベクトルにする)して一つ目にぶち込む

			switch (player.state)
			{
			case BLOCK_STING:
				player.m_ang = 0.0;//初期状態は加速度ゼロ
				player.ang = atan2(player.pdir.y, player.pdir.x);//初期角度を設定する

				player.state = PLAY_AIR;

				break;

			case PLAY_AIR:
				D3DXVECTOR2 axis_x(1.0f, 0.0f);//X軸ベクトル

				//X軸ベクトルとpdirとで内積を計算して、ブロックより右にいるか左にいるかを調べる
				//戻ってきた値がプラスの値なら右側、マイナスの値なら左側になる
				float lr = D3DXVec2Dot(&player.pdir, &axis_x);

				//振り子のスピードはここを変える
				float speed = 0.003f;

				//糸の長さはここを変える
				float ito_len = 150.0f;

				//lrがマイナスなら左側なので加速度を減算していく
				if (lr < 0.0f)
					player.m_ang -= speed;
				//lrがプラスなら右側なので加速度を加算していく
				else
					player.m_ang += speed;

				//角度の更新
				player.ang += player.m_ang;

				//座標の更新
				Chara.pos.x = pBlock[i]->GetPos().x + cos(player.ang) * ito_len;
				Chara.pos.y = pBlock[i]->GetPos().y + sin(player.ang) * ito_len;
			}

		}
	}

	//ターザンから着地の処理
	if ((GetKeyboardTrigger(DIK_SPACE) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) && player.tarzan == true)
	{
		

		TarzanExit();
	}

	//梯子処理

	if (bl->GetCheckLadder() == true) {
		for (int i = 0; i < game()->GetOm()->GetTotalLadder(); i++) {
			if (ladder[i]->GetHit() == false)
				continue;

			dif_ladder.x = Chara.pos.x - ladder[i]->GetPos().x;
			dif_ladder.y = Chara.pos.y - ladder[i]->GetPos().y + 128.0f;

			D3DXVec2Normalize(&dif_ladder, &dif_ladder);
			if (!HitCheckField(Chara.pos, 64.0f, 64.0f, ladder[i]->GetPos(), 64.0f, 128.0f)) {
				Chara.pos -= dif_ladder * 3.0f;

			}
			else {
				Chara.pos.x += 64.0f;
				bl->SetCheckLadder(false);
			}
		}
	}



	//カメラ座標の更新
	CAMERA_2D* pCamera = game()->GetCamera();
	pCamera->SetPosX(Chara.pos.x - PLAYER_DISP_X);
	pCamera->SetPosY(Chara.pos.y - PLAYER_DISP_Y);
	//ステージの左端
	if (pCamera->GetPos().x < 0)
		pCamera->SetPosX(0);

	//ステージの右端
	if (pCamera->GetPos().x > SCREEN_WIDTH * 6 - 48.0f)
		pCamera->SetPosX(SCREEN_WIDTH * 6 - 48.0f);

	//ステージの上側
	if (pCamera->GetPos().y < 0)
		pCamera->SetPosY(0);

	//ステージの下側
	if (pCamera->GetPos().y > SCREEN_HEIGHT - 8.0f)
		pCamera->SetPosY(SCREEN_HEIGHT - 8.0f);
}

void Player::Anime(void)
{
	//==========================================
	//針を投げるアニメーション
	//==========================================
	if (player.pattern == 7 || player.pattern == 8)
	{
		if (player.animeCounter > 5)
		{
			//アニメーションパターンを切り替える
			player.animePtn++;
			if (player.flag_throw == true && player.animePtn >= 3 && X_GetRightTrigger(0)) {
				player.animePtn = 3;

			}
			if (player.flag_throw == true && player.animePtn == 5 && !X_GetRightTrigger(0)) {
				ThrowThread();
				PlaySound(m_SENo, 0); //投げる音
				player.flag_throw = false;
			}
			else if (player.flag_throw == false && player.animePtn >= 9) {
				if (player.pattern == 7) {
					player.pattern = 1;
					player.animePtn = 0;

				}
				else if (player.pattern == 8) {
					player.pattern = 2;
					player.animePtn = 0;
				}
			}


			//アニメーションカウンターのリセット
			player.animeCounter = 0;
		}
	}


	//敵と衝突していなかったら
	if (!player.hit_anime) {
		//==========================================
		//待機のアニメーション
		//==========================================
		if (player.pattern == 1 || player.pattern == 2) {
			if (player.animeCounter > 30)
			{
				//アニメーションパターンを切り替える
				player.animePtn++;
				//最後のアニメーションパターンを表示したらリセットする
				if ((player.pattern == 1 || player.pattern == 2) && player.animePtn >= 2) {
					player.animePtn = 0;
				}
				//アニメーションカウンターのリセット
				player.animeCounter = 0;
			}
		}

		//==========================================
		//歩きアニメーション
		//==========================================
		if (player.pattern == 3 || player.pattern == 4 || player.pattern == 5 || player.pattern == 6) {
			if (player.animeCounter > 5)
			{
				//アニメーションパターンを切り替える
				player.animePtn++;
				//最後のアニメーションパターンを表示したらリセットする
				if ((player.pattern == 1 || player.pattern == 2) && player.animePtn >= 2) {
					player.animePtn = 0;
				}
				else if ((player.pattern == 3 || player.pattern == 4 || player.pattern == 5 || player.pattern == 6) && player.animePtn >= 8) {

					player.animePtn = 0;
				}
				//アニメーションカウンターのリセット
				player.animeCounter = 0;
			}
		}
	}

	//==========================================
	//敵との衝突アニメーション
	//==========================================
	if (player.pattern == 9 || player.pattern == 10)
	{
		if (player.animeCounter > 10)
		{
			//アニメーションパターンを切り替える
			player.animePtn++;

			if (player.animePtn >= 7) {

				if (player.pattern == 9) {
					player.pattern = 1;
					player.animePtn = 0;

				}
				else if (player.pattern == 10) {
					player.pattern = 2;
					player.animePtn = 0;
				}
				player.hit_anime = false;
				player.hit_enemy = false;
			}


			//アニメーションカウンターのリセット
			player.animeCounter = 0;
		}
	}
	player.animeCounter++;
}

//=============================================================================
//攻撃処理
//=============================================================================
void Player::AttackSting()
{

	Sew();
}

void Player::ThrowThread()
{
	//弾の発射処理
	bl->SetBullet(Chara.pos, player.pattern, player.rot);
	player.flag_throw = false;
	Chara.speed = 0.0f;
	Chara.speedY = 0.0f;
	player.rot = 0.0f;
	player.speed_rot = 0.0f;
}

//===================================================================
// プレイヤーと弾の衝突判定
//===================================================================
void Player::HitBullet()
{
	BLOCK* blo[MAX_BLOCK];

	for (int i = 0; i < MAX_BLOCK; i++)
		blo[i] = game()->GetOm()->GetBlock(i);

	if (bl->GetFrame() <= 240) {//弾の出現時に判定をさせない
		if (HitCheckBox(Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, bl->GetPos(), 64.0f, 16.0f)) {
			dir_bullet = D3DXVECTOR2(0.0f, 0.0f);
			bl->SetUse(false);
			for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++)
				blo[i]->Hitbullet(false);
		}
	}
}


void Player::JumpSet(void)
{
	//ジャンプ力の初期値をセット
	player.jumpPower = 8.0f;
	player.gravity = 0.33f;
	pos_jump = Chara.pos.y;
	Chara.fieldstand = false;
	player.jumpFlag = true;
}

bool Player::GetPatternR(void)
{
	if (player.pattern % 2 == 0)
		return true;

	return false;
}

bool Player::GetPatternL(void)
{
	if (player.pattern % 2 != 0)
		return true;

	return false;
}

//===================================================================
// 敵を縫うまでの処理
//===================================================================
void Player::Sew(void) {


	Enemy_Field* ef[ENEMY_FIELD_MAX];
	Enemy_Bird* ew[BIRD_MAX];
	Enemy_Bee* es[BEE_MAX];

	BOSS* boss = nullptr;
	for (int i = 0; i < cm->GetEnemyfTotal(); i++)
		ef[i] = cm->GetEnemyField(i);
	for (int i = 0; i < cm->GetEnemywTotal(); i++)
		ew[i] = cm->GetBird(i);
	for (int i = 0; i < cm->GetEnemysTotal(); i++)
		es[i] = cm->GetBee(i);

	if (game()->map()->GetBossFlag() == true)
		boss = cm->GetBoss();
	for (int i = 0; i < cm->GetEnemyfTotal(); i++) {//クマ

		if (ef[i]->GetSave() == false)
			continue;

		if (ef[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = ef[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 390.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				ef[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//敵はスティック一周でダメージ
			}
		}

	}
	for (int i = 0; i < cm->GetEnemywTotal(); i++) {//鳥

		if (ew[i]->GetSave() == false)
			continue;

		if (ew[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = ew[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 325.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				ew[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//敵はスティック一周でダメージ
			}
		}

	}

	for (int i = 0; i < cm->GetEnemysTotal(); i++) {//蜂

		if (es[i]->GetSave() == false)
			continue;

		if (es[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = es[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 465.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				es[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//敵はスティック一周でダメージ
			}
		}
	}

	if (boss != nullptr) {
		if (boss->GetUse() == true) {
			if (bl->GetHitBoss() && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {

				player.attack_cnt++;
				if (player.attack_cnt >= 8) {

					boss->SetDamage(1);

					player.attack_cnt = 0;
					player.damage_cnt++;
					if (boss->hp() <= 0) {

						bl->SetUse(false);
						boss->SetHitBullet(false);
					}
				}
			}
		}
	}
}

void Player::TarzanExit(void)
{
	player.tarzan = false;
	bl->SetCheck(false);
	bl->SetUse(false);
	Chara.vel.y = 0.0f;
	player.state = PLAY_NUM;
	BLOCK* blo[MAX_BLOCK];

	for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++) {
		blo[i] = game()->GetOm()->GetBlock(i);
		blo[i]->Hitbullet(false);

	}

	JumpSet();
}

/*
糸巻きゲージの処理

	総量100
	20%ごとに描画を変える

	敵
	針が敵に当たったら針は残る
	刺さった状態で自分がダッシュは不可能
	刺さった状態で回収すると針が抜ける
	この時は糸の消費はない
	プレイヤーと敵が近ければ縫うことが可能
	この時に糸を消費

	橋
	両端に木の杭が刺さっていて
	反対側の杭に刺さった状態で縫うと反対側から描画
	少しずつ縫っていくから途中で止めて、一定時間経過したら徐々に消していく

	橋が完成したタイミングで糸が消費される

*/