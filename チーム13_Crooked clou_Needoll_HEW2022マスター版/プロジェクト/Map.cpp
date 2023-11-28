/*==============================================================================

   �}�b�v�Ǘ� [Map.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "map.h"
#include "camera.h"
#include "collision.h"
#include "Fieldcollision.h"
#include "player.h"
#include "sprite.h"
#include "texture.h"
#include "Game.h"
#include "CharacterManager.h"
#include <stdio.h>
#include "SceneManager.h"
#include "Bullet.h"
#include "BulletCollision.h"
#include "ObjectManager.h"
#include "Boss.h"
#include "BossArm.h"
#include "EnemyBullet.h"
#include "BeeBullet.h"
#include "Enemy_Field.h"
#include "Enemy_Bee.h"
#include "Bridge.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define DIVIDE_X 8	//���̕�����
#define DIVIDE_Y 8	//�c�̕�����

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int   g_TextureName = 0;
FILE *fpMap;


static float g_MapBaseType[8] = {
	0.0f,	//�ʏ�̑���
	0.125f,	//�[������
	0.25f,	//���邢����
	0.375f,	//�Â�����
	0.5f,	//�y
	0.625f,	//�r��y
	0.75f,	//����
	0.875f,	//���H
};



MAP::MAP(class Game* game, int stage) :GameObject(game)
{

	m_stage = stage;
}

//=============================================================================
// ����������
//=============================================================================
void MAP::InitMap(void)
{


	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	CharacterManager* cm = game()->GetCm();
	ObjectManager* om = game()->GetOm();


	int col = 0;
	int row = 0;
	fpMap = fopen(fname[m_stage], "r");
	if (fpMap != NULL) {
		while (!feof(fpMap)) {
			char ch;
			ch = fgetc(fpMap);
			if (ch == -1)
				break;
			if (ch == '\n')
			{
				row++;
				col = 0;
			}
			//�G��M�~�b�N�Ȃǃ}�b�v�ɒǉ�������̂͂����ɋL�q
			//CM
			else if (ch == 'p') {
				cm->create(0, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'f') {
				cm->create(1, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 't') {//t�E�E�E�w�
				cm->create(2, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'c') {
				cm->create(3, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
				boss_flag = true;
			}
			//�{���ǉ�-----------------------------------------------------
			else if (ch == 'w') {//w�E�E�E��(wing)
				cm->create(4, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 's') {//b�E�E�E�I(sting)
				cm->create(5, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}

			//OM
			else if (ch == 'b') {
				om->create(0, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'l') {
				om->create(1, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'i') {
				om->create(2, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'd') {
				om->create(3, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'h') {
				om->create(4, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'g')
			{
				om->create(5, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			//�{���ǉ�
			else if (ch == 'm') {//�|�[��
				om->create(6, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'j')
			{
				om->create(7, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'q')//DownBlock
			{
				om->create(8, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'k')
			{
				om->create(9, D3DXVECTOR2(col*32.0f, row*32.0f));
				col++;
			}
			else if (ch == 'n')
			{
				om->create(10, D3DXVECTOR2(col*32.0f, row*32.0f));//���鎅����
				col++;
			}
			else if (ch != ',') {//�u,�v�ȊO��������
				m_Mesh[row][col++].mesh = atoi(&ch);
			}
		}
		fclose(fpMap);
	}
	else {
		//�ǂݍ��߂Ȃ������Ƃ��̃G���[
		//�f�o�b�N���O�ɕ\��
		OutputDebugString("<^^^^^^^^^^^^^^^^^^^^^^^^^^^^>\n");
		OutputDebugString("<�}�b�v���ǂݍ��߂܂���ł���>\n");
		OutputDebugString("<vvvvvvvvvvvvvvvvvvvvvvvvvvvv>\n");
		error_flag = true;
	}

	g_TextureName = LoadTexture((char*)"data/TEXTURE/mapchip.png");

	m_BGMNo = LoadSound((char*)"data/BGM/akaruino2.wav");
	SENo = LoadSound((char*)"data/SE/�j���͂�����鉹.wav");

	PlaySound(m_BGMNo, -1);

}

//=============================================================================
// �I������
//=============================================================================
void MAP::UninitMap(void)
{
	StopSoundAll();

}

//=============================================================================
// �X�V����
//=============================================================================
void MAP::UpdateMap(void)
{

	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	Player* pPlayer = game()->GetCm()->GetPlayer();
	BULLET* pBullet = game()->GetBullet();

	//�{���ǉ�
	ENEMYBULLET* pEnBullet = game()->GetEnemyBullet();
	BEEBULLET* pBeeBullet = game()->GetBeeBullet();

	Bridge* pBridge[BRIDGE_POAL];
	for (int i = 0; i < game()->GetOm()->GetPoalTotal(); i++) {
		pBridge[i] = game()->GetOm()->GetBridge(i);
	}

	Enemy_Field* pEnField[ENEMY_FIELD_MAX];//�{���͍ő吔�ł͂Ȃ��A���ꂽ�������Ă�
	for (int i = 0; i < game()->GetCm()->GetEnemyfTotal(); i++) {
		pEnField[i] = game()->GetCm()->GetEnemyField(i);
	}

	Enemy_Bee* pEnBee[BEE_MAX];//�{���͍ő吔�ł͂Ȃ��A���ꂽ�������Ă�
	for (int i = 0; i < game()->GetCm()->GetEnemysTotal(); i++) {
		pEnBee[i] = game()->GetCm()->GetBee(i);
	}

	for (int y = 0; y < MAX_YMAP; y++)
	{
		for (int x = 0; x < MAX_XMAP; x++)
		{
			if (m_Mesh[y][x].mesh == 7) {
				m_Mesh[y][x].brpos.x = 32.0f * x;
				m_Mesh[y][x].brpos.y = 32.0f * y;
			}

			//�������ȊO�̓����蔻��(���Ȃ�)
			else if (m_Mesh[y][x].mesh != 0)
			{
				m_Mesh[y][x].pos.y = basePos.y + (32.0f * y);
				m_Mesh[y][x].pos.x = basePos.x + (32.0f * x);
				m_Mesh[y][x].collipos.x = 32.0f * x;
				m_Mesh[y][x].collipos.y = 32.0f * y;

			}
		}
	}


	for (int y = 0; y < MAX_YMAP; y++)
	{
		for (int x = 0; x < MAX_XMAP; x++)
		{
			//==============================================================================
			//�v���C���[�ƒn�ʁA�ǂ̏Փ˔���
			//==============================================================================
			if (HitCheckBox(pPlayer->Chara.pos, PLAYER_SIZE_X + 20, PLAYER_SIZE_Y + 20, m_Mesh[y][x].collipos, 32.0f, 32.0f))
			{
				if (HitCheckField(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_Mesh[y][x].collipos, 32.0f, 32.0f))
				{
					if (pPlayer->GetJumpFlag() == true) {
						pPlayer->SetOldJump(m_Mesh[y][x].collipos.y - 90);
						pPlayer->SetJumpFlag(false);
					}
					pPlayer->Chara.pos.y = m_Mesh[y][x].collipos.y - 90.0f;
					pPlayer->Chara.gravityscale = 0.0f;
					if (pPlayer->GetTarzanFlag() == true) {
						pPlayer->SetTarzan(false);
						pBullet->SetCheck(false);
					}
				}
				else if (HitCheckwallleft(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_Mesh[y][x].collipos, 32.0f, 32.0f))
				{
					pPlayer->Chara.pos.x = m_Mesh[y][x].collipos.x + 66.0f;
					pPlayer->Chara.moveinpulse = 0.0f;
					if (pPlayer->GetTarzanFlag() == true) {
						pPlayer->SetTarzan(false);
						pBullet->SetCheck(false);
					}
				}
				else if (HitCheckwallright(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_Mesh[y][x].collipos, 32.0f, 32.0f))
				{
					pPlayer->Chara.pos.x = m_Mesh[y][x].collipos.x - 66.0f;
					pPlayer->Chara.moveinpulse = 0.0f;
					if (pPlayer->GetTarzanFlag() == true)
						pPlayer->SetTarzan(false);
					pBullet->SetCheck(false);
				}
				else if (HitCheckCelling(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, m_Mesh[y][x].collipos, 32.0f, 32.0f))
				{
					pPlayer->SetJumpPow(0.0f);
					pPlayer->Chara.pos.y = m_Mesh[y][x].collipos.y + 90.0f;
					if (pPlayer->GetTarzanFlag() == true)
						pPlayer->SetTarzan(false);
					pBullet->SetCheck(false);
				}

				if (HitCheckBox(pPlayer->Chara.pos, PLAYER_SIZE_X + 20, PLAYER_SIZE_Y + 20, m_Mesh[y][x].collipos, 32.0f, 32.0f))
				{
					pPlayer->Chara.fieldstand = true;

				}

			}

			//==============================================================================
			//�j(�e)�ƒn�ʁA�ǂ̏Փ˔���
			//==============================================================================
			if (HitCheckBox(pBullet->GetPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
				//��
				if (HitCheckBField(pBullet->GetPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pBullet->SetHitField(true);
				}
				//�V��
				else if (HitCheckBCelling(pBullet->GetPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {

					pBullet->SetVelY();
				}
				//�E��
				else if (HitCheckBwallright(pBullet->GetPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {

					pBullet->SetVelX();
				}
				//����
				else if (HitCheckBwallleft(pBullet->GetPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {

					pBullet->SetVelX();
				}
			}

			if (boss_flag == true) {
				BOSS* boss = game()->GetCm()->GetBoss();

				if (HitCheckBox(boss->GetPos(), BOSS_SIZE_X, BOSS_SIZE_Y, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					boss->SetHitField(true);
				}
			}
			if (boss_flag == true) {
				BOSSARM* arm_r = game()->GetCm()->GetBoss()->GetArmR();
				BOSSARM* arm_l = game()->GetCm()->GetBoss()->GetArmL();

				if (arm_l != nullptr && arm_r != nullptr) {
					//==============================================================================
					//�{�X�r�ƒn��
					//==============================================================================
					if (HitCheckBox(arm_l->GetPos(), 200.0f, 100.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						/*if (HitCheckArmField(arm_l->GetPos(), 200.0f, 100.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						}*/
						arm_l->SetHitField(true);
					}
					if (HitCheckBox(arm_r->GetPos(), 200.0f, 100.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						/*if (HitCheckArmField(arm_r->GetPos(), 200.0f, 100.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						}*/
						arm_r->SetHitField(true);
					}
				}
			}

			//�{���ǉ�
			//==============================================================================
			//�e(��)�ƒn�ʁA�ǂ̏Փ˔���
			//==============================================================================
			if (HitCheckBox(pEnBullet->GetEbPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
				//�� 
				if (HitCheckBField(pEnBullet->GetEbPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pEnBullet->Delete();
				}
				//�V��
				else if (HitCheckBCelling(pEnBullet->GetEbPos(), 64.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pEnBullet->Delete();
				}
				//�E��
				else if (HitCheckBwallright(pEnBullet->GetEbPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pEnBullet->Delete();
				}
				//����
				else if (HitCheckBwallleft(pEnBullet->GetEbPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pEnBullet->Delete();
				}
			}

			//==============================================================================
			//�e(�I)�ƒn�ʁA�ǂ̏Փ˔���
			//==============================================================================
			if (HitCheckBox(pBeeBullet->GetBbPos(), 64.0f, 64.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
				//�� 
				if (HitCheckBField(pBeeBullet->GetBbPos(), 16.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pBeeBullet->Delete();
				}
				//�V��
				else if (HitCheckBCelling(pBeeBullet->GetBbPos(), 16.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pBeeBullet->Delete();
				}
				//�E��
				else if (HitCheckBwallright(pBeeBullet->GetBbPos(), 16.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pBeeBullet->Delete();
				}
				//����
				else if (HitCheckBwallleft(pBeeBullet->GetBbPos(), 16.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
					pBeeBullet->Delete();
				}
			}

			//==============================================================================
			//�F�ƕǂ̏Փ˔���
			//==============================================================================	
			for (int i = 0; i < game()->GetCm()->GetEnemyfTotal(); i++)
			{
				if (pEnField[i] != nullptr)
				{
					//�E��	
					if (HitCheckBwallright(pEnField[i]->GetEnFieldPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						pEnField[i]->ReverseEfX();
					}
					//����
					if (HitCheckBwallleft(pEnField[i]->GetEnFieldPos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						pEnField[i]->ReverseEfX();

					}
				}
				
			}

			//==============================================================================
			//�I�ƕǂ̏Փ˔���
			//==============================================================================	
			for (int i = 0; i < game()->GetCm()->GetEnemysTotal(); i++)
			{
				if (pEnBee[i] != nullptr)
				{
					//�E��	
					if (HitCheckBwallright(pEnBee[i]->GetEnBeePos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						pEnBee[i]->ReverseEbX();
					}
					//����
					if (HitCheckBwallleft(pEnBee[i]->GetEnBeePos(), 70.0f, 16.0f, m_Mesh[y][x].collipos, 32.0f, 32.0f)) {
						pEnBee[i]->ReverseEbX();

					}
				}
				
			}

			//==============================================================================
			//���������������̏Փ˔���
			//==============================================================================	
			for (int i = 0; i < game()->GetOm()->GetPoalTotal(); i++)
			{
				//�Z�����̎�
				if (game()->GetOm()->GetBridge(i)->GetBuildS() == true)
				{
					if (HitCheckField(pPlayer->Chara.pos, 64.0f, 64.0f, m_Mesh[y][x].brpos, 32.0f, 32.0f)) {
						if (pPlayer->GetJumpFlag() == true) {
							pPlayer->SetOldJump(m_Mesh[y][x].brpos.y - 48.0f);
							pPlayer->SetJumpFlag(false);
						}
						pPlayer->Chara.pos.y = m_Mesh[y][x].brpos.y - 48.0f;
						pPlayer->Chara.gravityscale = 0.0f;
					}

					if (HitCheckBox(pPlayer->Chara.pos, 40.0f, 67.0f, m_Mesh[y][x].brpos, 32.0f, 32.0f))
					{
						pPlayer->Chara.fieldstand = true;

					}
				}

				//�������̎�
				if (game()->GetOm()->GetBridge(i)->GetBuildL() == true)
				{
					if (HitCheckField(pPlayer->Chara.pos, 64.0f, 64.0f, m_Mesh[y][x].brpos, 32.0f, 32.0f)) {
						if (pPlayer->GetJumpFlag() == true) {
							pPlayer->SetOldJump(m_Mesh[y][x].brpos.y - 48.0f);
							pPlayer->SetJumpFlag(false);
						}
						pPlayer->Chara.pos.y = m_Mesh[y][x].brpos.y - 48.0f;
						pPlayer->Chara.gravityscale = 0.0f;
					}

					if (HitCheckBox(pPlayer->Chara.pos, 40.0f, 67.0f, m_Mesh[y][x].brpos, 32.0f, 32.0f))
					{
						pPlayer->Chara.fieldstand = true;

					}
				}
			}
		}
	}

	//==============================================================================
	//�v���C���[�ƃ^�[�U���u���b�N�̏Փ˔���
	//==============================================================================
	for (int i = 0; i < game()->GetOm()->GetTotalBlock(); i++) {


		if (HitCheckBox(pPlayer->Chara.pos, 70.0f, PLAYER_SIZE_Y - 10.0f, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
		{
			if (HitCheckField(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
			{
				if (pPlayer->GetJumpFlag() == true) {
					pPlayer->SetOldJump(game()->GetOm()->GetBlock(i)->GetPos().y - 90);
					pPlayer->SetJumpFlag(false);
				}
				pPlayer->Chara.pos.y = game()->GetOm()->GetBlock(i)->GetPos().y - 90.0f;
				pPlayer->Chara.gravityscale = 0.0f;
				if (pPlayer->GetTarzanFlag() == true) {
					pPlayer->SetTarzan(false);
					pBullet->SetCheck(false);
				}
			}
			else if (HitCheckwallleft(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
			{
				pPlayer->Chara.pos.x = game()->GetOm()->GetBlock(i)->GetPos().x + 66.0f;
				pPlayer->Chara.moveinpulse = 0.0f;
				if (pPlayer->GetTarzanFlag() == true) {
					pPlayer->SetTarzan(false);
					pBullet->SetCheck(false);
				}
			}
			else if (HitCheckwallright(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
			{
				pPlayer->Chara.pos.x = game()->GetOm()->GetBlock(i)->GetPos().x - 66.0f;
				pPlayer->Chara.moveinpulse = 0.0f;
				if (pPlayer->GetTarzanFlag() == true)
					pPlayer->SetTarzan(false);
				pBullet->SetCheck(false);
			}
			else if (HitCheckCelling(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
			{
				pPlayer->SetJumpPow(0.0f);
				pPlayer->Chara.pos.y = game()->GetOm()->GetBlock(i)->GetPos().y + 90.0f;
				if (pPlayer->GetTarzanFlag() == true)
					pPlayer->SetTarzan(false);
				pBullet->SetCheck(false);
			}


		}

		if (HitCheckBox(pPlayer->Chara.pos, PLAYER_SIZE_X, PLAYER_SIZE_Y, game()->GetOm()->GetBlock(i)->GetPos(), 32.0f, 32.0f))
		{
			pPlayer->Chara.fieldstand = true;

		}
	}

}



//=============================================================================
// �`�揈��
//=============================================================================
void MAP::DrawMap(void)
{

	//�x�[�X���W���󂯎��
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	Character* pPlayer = game()->GetCm()->GetPlayer();

	//�x�[�X���C���[�̕`��
	for (int y = 0; y < MAX_YMAP; y++)
	{
		for (int x = 0; x < MAX_XMAP; x++)
		{
			DrawSprite(g_TextureName, m_Mesh[y][x].pos.x, m_Mesh[y][x].pos.y, 32.0f, 32.0f,
				g_MapBaseType[m_Mesh[y][x].mesh],
				0.0f,
				PATTERN_WIDTH,
				PATTERN_HEIGHT);
		}
	}


}

D3DXVECTOR2 MAP::GetMeshColliPos(int x, int y)
{
	return m_Mesh[y][x].collipos;
}
