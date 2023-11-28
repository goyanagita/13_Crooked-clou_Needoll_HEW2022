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
	0.0f,					//L����		1
	PATTERN_HEIGHT,			//R����		2
	PATTERN_HEIGHT * 20.0f,	//L��1���  3
	PATTERN_HEIGHT * 22.0f,	//R��1���  4
	PATTERN_HEIGHT * 21.0f,	//L���j���� 5
	PATTERN_HEIGHT * 23.0f,	//R���j���� 6
	PATTERN_HEIGHT * 12.0f,	//L�j����	7
	PATTERN_HEIGHT * 11.0f,	//R�j����	8
	PATTERN_HEIGHT * 4.0f,	//L�_���[�W	9
	PATTERN_HEIGHT * 5.0f,	//R�_���[�W	10

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
// ����������
//===================================================================

void Player::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/���C���L����_�`�b�v(�C���j.png");
	m_SENo = LoadSound((char*)"data/SE/throw.wav");
	m_SENo2 = LoadSound((char*)"data/SE/����.wav");
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


	//�K�v�ȏ����擾����
	cm = game()->GetCm();
	bl = game()->GetBullet();
	tg = game()->GetTg();
	ladder[0] = game()->GetOm()->GetLadder(0);

	player.survFlag = true;

	//�{���ǉ�
	om = game()->GetOm();
}

//===================================================================
// �I������
//===================================================================
void Player::Uninit()
{
	StopSoundAll();

}

//===================================================================
// �X�V����
//===================================================================
void Player::Update()
{
	//���W�̍X�V
	Chara.pos += Chara.vel;
	Chara.vel.x = 0.0f;

	//������Ԃ���Ȃ���Έړ���
	if (player.flag_throw != true) {

		if (player.walk && Chara.fieldstand) {
			player.walk_sound_frame++;
			//������
			if (player.walk_sound_frame >= 60) {
				PlaySound(m_SENo2, 0);
				player.walk_sound_frame = 0;
			}

		}	

		MovePlayer();
	}

	//������Ԉڍs����()
	if (player.flag_throw == false && (GetKeyboardTrigger(DIK_K) || X_GetRightTrigger(0))) {
		//������
		if (GetPatternL()) {
			player.pattern = 7;
			player.animePtn = 0;
		}
		//�E����
		else if (GetPatternR()) {
			player.pattern = 8;
			player.animePtn = 0;
		}
		player.flag_throw = true;
	}

	//�����ҋ@��ԂŉE���͂��ꂽ�Ƃ�
	if ((GetKeyboardPress(DIK_D) || X_GetThumbLeftX(0) > 0) && player.flag_throw == true) {
		if (Chara.speed <= 6.0f) {
			Chara.speed += 0.1f;
			if (player.pattern == 7) {
				//�������Ă�Ƃ�
				Chara.speedY -= 0.1f;
				if (player.rot <= 0.75f)
					player.rot += 0.01f;
			}
			else if (player.pattern == 8) {
				//�E�����Ă���Ƃ�
				Chara.speedY += 0.05f;
				if (player.rot <= 0.5f)
					player.rot += 0.01f;
			}
		}
	}

	//�����ҋ@��Ԃō����͂��ꂽ�Ƃ�
	if ((GetKeyboardPress(DIK_A) || X_GetThumbLeftX(0) < 0) && player.flag_throw == true) {
		if (Chara.speed >= -6.0f) {
			Chara.speed -= 0.1f;

			if (player.pattern == 7) {
				//�������Ă���Ƃ�
				Chara.speedY += 0.05f;
				if (player.rot >= -0.5f)
					player.rot -= 0.01f;

			}
			else if (player.pattern == 8) {
				//�E�����Ă���Ƃ�
				Chara.speedY -= 0.1f;
				if (player.rot >= -0.75f)
					player.rot -= 0.01f;
			}
		}
	}

	//�j���n�ʂɎh�����Ă���Ƃ������j�ƃv���C���[�̋������v�Z
	if (bl->GetHitField() == true) {
		dir_bullet = Chara.pos - bl->GetPos();
		D3DXVec2Normalize(&dir_bullet, &dir_bullet);

	}

	//�j���h�����Ă���Ƃ�����
		//�j�̉��
	if ((GetKeyboardPress(DIK_O) || X_RotateRThumbRight(0)) && bl->GetUse() == true && bl->GetHit() != true && bl->GetHitPoal() == false) {
		bl->SetPos(dir_bullet);

	}
	
	//�j�̕��Ƀ_�b�V��
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

	//�{���ǉ�
	for (int i = 0; i < om->GetPoalTotal(); i++) {
		if (game()->GetOm()->GetBridge(i)->GetBuildS() ||
			game()->GetOm()->GetBridge(i)->GetBuildL()) {
			bl->SetUse(false);
		}
	}

	//=================================
	//�G�Ɠ��������Ƃ��ɃA�j���[�V����
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

	//�����鏈��
	AttackSting();

	//�v���C���[�Ɛj�̏Փ˔���
	HitBullet();

	//���S����
	if (Chara.pos.y >= 1200) {
		Chara.hp = 0;
	}
	if (Chara.hp <= 0) {
		player.survFlag = false;
	}
}

//===================================================================
// �`�揈��
//===================================================================
void Player::Draw()
{
	//�x�[�X���W���󂯎��
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();

	//�L�����N�^�[�̕`��
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
//�ړ��n����
//=============================================================================
void Player::MovePlayer()
{
	player.walk = false;
	player.pos_old.x = Chara.pos.x;//�ړ�����O�Ɍ��ݍ��W���ړ��O�̍��W�ɕۑ����Ă���

	//�d�͂ł̗�������
	if (Chara.fieldstand == false && player.jumpFlag == false && bl->GetCheckLadder() != true) {
		Chara.vel.y += player.gravity_fall;
	}
	//���n��������
	if (Chara.fieldstand == true) {
		player.gravity_fall = 0.0f;
		Chara.vel.y = 0.0f;
	}
	else {
		player.gravity_fall = 0.3f;
	}
	Chara.fieldstand = false;



	//==========================================
	//�������[�V�����A�G�Ƃ̏Փ˂��Ȃ���Ε�����
	//==========================================
	if (!player.flag_throw && player.hit_anime == false) {
		//�������ւ̈ړ�
		if (GetKeyboardPress(DIK_A) || X_GetThumbLeftX(0) < 0)
		{
			player.walk = true;
			if (player.pattern != 5)
				player.pattern = 3;
			Chara.vel.x = -4.0f;

			if (player.tarzan == false)
				a = true;

		}

		//�E�����ւ̈ړ�
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
		//��������߂����ɃA�j���[�V������ҋ@�ɂ���
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


	//�W�����v����(�W�����v���ł͂Ȃ���ԂŃX�y�[�X�L�[�������ꂽ�Ƃ�)
	if ((GetKeyboardTrigger(DIK_SPACE) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) && (player.jumpFlag == false) && player.tarzan == false)
	{

		JumpSet();
	}

	//�W�����v���̏���
	if (player.jumpFlag == true)
	{
		//�����̍X�V
		player.height += player.jumpPower;

		//�����̍X�V(�ʒu)
		Chara.pos.y -= player.jumpPower;

		//�W�����v�͂̌���
		player.jumpPower -= player.gravity;

		//�n�ʂɒ��n�����ꍇ
		if (Chara.fieldstand == true)
		{
			//������0�ɖ߂��ăW�����v���t���O�𗎂Ƃ�
			player.height = 0.0f;
			if (!player.tarzan)
				Chara.pos.y = pos_jump;
			player.jumpFlag = false;

		}
	}

	//�^�[�U���̏���
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
			vDif = pBlock[i]->GetPos() - Chara.pos;//�v���C���[����u���b�N�̕��Ɍ����x�N�g��
			float len = D3DXVec2Length(&vDif);
			D3DXVec2Normalize(&vDif, &vDif);//2�ڂ̈����𐳋K�����Ĉ�ڂɂԂ�����
			D3DXVec2Normalize(&player.pdir, &player.pdir);//2�ڂ̈����𐳋K��(1.0�̃x�N�g���ɂ���)���Ĉ�ڂɂԂ�����

			switch (player.state)
			{
			case BLOCK_STING:
				player.m_ang = 0.0;//������Ԃ͉����x�[��
				player.ang = atan2(player.pdir.y, player.pdir.x);//�����p�x��ݒ肷��

				player.state = PLAY_AIR;

				break;

			case PLAY_AIR:
				D3DXVECTOR2 axis_x(1.0f, 0.0f);//X���x�N�g��

				//X���x�N�g����pdir�Ƃœ��ς��v�Z���āA�u���b�N���E�ɂ��邩���ɂ��邩�𒲂ׂ�
				//�߂��Ă����l���v���X�̒l�Ȃ�E���A�}�C�i�X�̒l�Ȃ獶���ɂȂ�
				float lr = D3DXVec2Dot(&player.pdir, &axis_x);

				//�U��q�̃X�s�[�h�͂�����ς���
				float speed = 0.003f;

				//���̒����͂�����ς���
				float ito_len = 150.0f;

				//lr���}�C�i�X�Ȃ獶���Ȃ̂ŉ����x�����Z���Ă���
				if (lr < 0.0f)
					player.m_ang -= speed;
				//lr���v���X�Ȃ�E���Ȃ̂ŉ����x�����Z���Ă���
				else
					player.m_ang += speed;

				//�p�x�̍X�V
				player.ang += player.m_ang;

				//���W�̍X�V
				Chara.pos.x = pBlock[i]->GetPos().x + cos(player.ang) * ito_len;
				Chara.pos.y = pBlock[i]->GetPos().y + sin(player.ang) * ito_len;
			}

		}
	}

	//�^�[�U�����璅�n�̏���
	if ((GetKeyboardTrigger(DIK_SPACE) || X_IsButtonPressed(0, XINPUT_GAMEPAD_A)) && player.tarzan == true)
	{
		

		TarzanExit();
	}

	//��q����

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



	//�J�������W�̍X�V
	CAMERA_2D* pCamera = game()->GetCamera();
	pCamera->SetPosX(Chara.pos.x - PLAYER_DISP_X);
	pCamera->SetPosY(Chara.pos.y - PLAYER_DISP_Y);
	//�X�e�[�W�̍��[
	if (pCamera->GetPos().x < 0)
		pCamera->SetPosX(0);

	//�X�e�[�W�̉E�[
	if (pCamera->GetPos().x > SCREEN_WIDTH * 6 - 48.0f)
		pCamera->SetPosX(SCREEN_WIDTH * 6 - 48.0f);

	//�X�e�[�W�̏㑤
	if (pCamera->GetPos().y < 0)
		pCamera->SetPosY(0);

	//�X�e�[�W�̉���
	if (pCamera->GetPos().y > SCREEN_HEIGHT - 8.0f)
		pCamera->SetPosY(SCREEN_HEIGHT - 8.0f);
}

void Player::Anime(void)
{
	//==========================================
	//�j�𓊂���A�j���[�V����
	//==========================================
	if (player.pattern == 7 || player.pattern == 8)
	{
		if (player.animeCounter > 5)
		{
			//�A�j���[�V�����p�^�[����؂�ւ���
			player.animePtn++;
			if (player.flag_throw == true && player.animePtn >= 3 && X_GetRightTrigger(0)) {
				player.animePtn = 3;

			}
			if (player.flag_throw == true && player.animePtn == 5 && !X_GetRightTrigger(0)) {
				ThrowThread();
				PlaySound(m_SENo, 0); //�����鉹
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


			//�A�j���[�V�����J�E���^�[�̃��Z�b�g
			player.animeCounter = 0;
		}
	}


	//�G�ƏՓ˂��Ă��Ȃ�������
	if (!player.hit_anime) {
		//==========================================
		//�ҋ@�̃A�j���[�V����
		//==========================================
		if (player.pattern == 1 || player.pattern == 2) {
			if (player.animeCounter > 30)
			{
				//�A�j���[�V�����p�^�[����؂�ւ���
				player.animePtn++;
				//�Ō�̃A�j���[�V�����p�^�[����\�������烊�Z�b�g����
				if ((player.pattern == 1 || player.pattern == 2) && player.animePtn >= 2) {
					player.animePtn = 0;
				}
				//�A�j���[�V�����J�E���^�[�̃��Z�b�g
				player.animeCounter = 0;
			}
		}

		//==========================================
		//�����A�j���[�V����
		//==========================================
		if (player.pattern == 3 || player.pattern == 4 || player.pattern == 5 || player.pattern == 6) {
			if (player.animeCounter > 5)
			{
				//�A�j���[�V�����p�^�[����؂�ւ���
				player.animePtn++;
				//�Ō�̃A�j���[�V�����p�^�[����\�������烊�Z�b�g����
				if ((player.pattern == 1 || player.pattern == 2) && player.animePtn >= 2) {
					player.animePtn = 0;
				}
				else if ((player.pattern == 3 || player.pattern == 4 || player.pattern == 5 || player.pattern == 6) && player.animePtn >= 8) {

					player.animePtn = 0;
				}
				//�A�j���[�V�����J�E���^�[�̃��Z�b�g
				player.animeCounter = 0;
			}
		}
	}

	//==========================================
	//�G�Ƃ̏Փ˃A�j���[�V����
	//==========================================
	if (player.pattern == 9 || player.pattern == 10)
	{
		if (player.animeCounter > 10)
		{
			//�A�j���[�V�����p�^�[����؂�ւ���
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


			//�A�j���[�V�����J�E���^�[�̃��Z�b�g
			player.animeCounter = 0;
		}
	}
	player.animeCounter++;
}

//=============================================================================
//�U������
//=============================================================================
void Player::AttackSting()
{

	Sew();
}

void Player::ThrowThread()
{
	//�e�̔��ˏ���
	bl->SetBullet(Chara.pos, player.pattern, player.rot);
	player.flag_throw = false;
	Chara.speed = 0.0f;
	Chara.speedY = 0.0f;
	player.rot = 0.0f;
	player.speed_rot = 0.0f;
}

//===================================================================
// �v���C���[�ƒe�̏Փ˔���
//===================================================================
void Player::HitBullet()
{
	BLOCK* blo[MAX_BLOCK];

	for (int i = 0; i < MAX_BLOCK; i++)
		blo[i] = game()->GetOm()->GetBlock(i);

	if (bl->GetFrame() <= 240) {//�e�̏o�����ɔ���������Ȃ�
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
	//�W�����v�͂̏����l���Z�b�g
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
// �G��D���܂ł̏���
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
	for (int i = 0; i < cm->GetEnemyfTotal(); i++) {//�N�}

		if (ef[i]->GetSave() == false)
			continue;

		if (ef[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = ef[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 390.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				ef[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//�G�̓X�e�B�b�N����Ń_���[�W
			}
		}

	}
	for (int i = 0; i < cm->GetEnemywTotal(); i++) {//��

		if (ew[i]->GetSave() == false)
			continue;

		if (ew[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = ew[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 325.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				ew[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//�G�̓X�e�B�b�N����Ń_���[�W
			}
		}

	}

	for (int i = 0; i < cm->GetEnemysTotal(); i++) {//�I

		if (es[i]->GetSave() == false)
			continue;

		if (es[i]->GetHitBullet() == true) {

			D3DXVECTOR2 distance = es[i]->Chara.pos - Chara.pos;

			float e_dist = D3DXVec2Length(&distance);

			if ((e_dist <= 465.0f) && ((GetKeyboardTrigger(DIK_U) || X_RotateRThumbRight(0)))) {
				es[i]->SetSave(false);
				tg->UseThread(USE_ENEMY);
				bl->SetUse(false);
				//�G�̓X�e�B�b�N����Ń_���[�W
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
�������Q�[�W�̏���

	����100
	20%���Ƃɕ`���ς���

	�G
	�j���G�ɓ���������j�͎c��
	�h��������ԂŎ������_�b�V���͕s�\
	�h��������Ԃŉ������Ɛj��������
	���̎��͎��̏���͂Ȃ�
	�v���C���[�ƓG���߂���ΖD�����Ƃ��\
	���̎��Ɏ�������

	��
	���[�ɖ؂̍Y���h�����Ă���
	���Α��̍Y�Ɏh��������ԂŖD���Ɣ��Α�����`��
	�������D���Ă�������r���Ŏ~�߂āA��莞�Ԍo�߂����珙�X�ɏ����Ă���

	�������������^�C�~���O�Ŏ���������

*/