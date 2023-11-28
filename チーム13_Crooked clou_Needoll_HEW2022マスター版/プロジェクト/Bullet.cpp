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
	D3DX_PI,		//������(180����]������)
	(-D3DX_PI / 2),	//������(-90����]������)
	(+D3DX_PI / 2),	//�E����(+90����]������)
	0.0f,			//�����
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BULLET::BULLET(class Game * game):GameObject(game)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/sting.png");
	SENo = LoadSound((char*)"data/SE/�_���[�W.wav");
	use = false;

	rot = 0.0f;
}

//=============================================================================
// ����������
//=============================================================================
void BULLET::Init()
{
	//�K�v�ȏ����擾����
	cm = game()->GetCm();

	//�{���ǉ�
	om = game()->GetOm();
	
}
//=============================================================================
// �I������
//=============================================================================
void BULLET::Uninit()
{
	StopSoundAll();

}

//=============================================================================
// �X�V����
//=============================================================================
void BULLET::Update()
{
	//�K�v�ȏ����擾
	BLOCK * bl[MAX_BLOCK] ;
	Ladder* la[MAX_LADDER];
	Enemy_Field* ef[ENEMY_FIELD_MAX];
	Enemy_Bird* ew[ENEMY_FIELD_MAX];
	Enemy_Bee* es[ENEMY_FIELD_MAX];
	Bridge* br[BRIDGE_POAL];//�{���ǉ�


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
	for (int i = 0; i < om->GetPoalTotal(); i++)//�{���ǉ�
		br[i] = om->GetBridge(i);

	if (use == true) {
		//�e�̍��W�X�V
		if (check != true && hit_field != true && check_ladder != true && hit_boss != true) {
			m_pos += vel;
			if (hit_enemy != true ) {
				vel.y += gravity.y;
				rot += rot_speed;
			}


		}

		//�L���t���[�������炷
		frame--;


		//�e�ƃu���b�N�̓����蔻��
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

		//�G�ƒe�̓����蔻��
		for (int i = 0; i < cm->GetEnemyfTotal(); i++) {//�N�}

			if (ef[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, ef[i]->Chara.pos, 85.0f, 115.0f)) {
				ef[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (ef[i]->GetVel())*-1;

				PlaySound(SENo, 0);

			}
		}
		for (int i = 0; i < cm->GetEnemywTotal(); i++) {//��

			if (ew[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, ew[i]->Chara.pos, 90.0f, 105.0f)) {
				ew[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (ew[i]->GetVel());

				PlaySound(SENo, 0);


			}
		}
		for (int i = 0; i < cm->GetEnemysTotal(); i++) {//�I

			if (es[i]->GetSave() == false)
				continue;

			if (HitCheckBox(m_pos, 64.0f, 64.0f, es[i]->Chara.pos, 128.0f, 128.0f)) {
				es[i]->SetHitBullet(true);
				hit_enemy = true;
				vel = (es[i]->GetVel());

				PlaySound(SENo, 0);


			}
		}

		//�{���ǉ�
		for (int i = 0; i < om->GetPoalTotal(); i++)
		{
			if (i % 2 == 1) {
				if (HitCheckBullet(m_pos, 45.0f, 64.0f, br[i]->GetPos(), 64.0f, 64.0f))
				{
					br[i]->SetHit(true);
					hit_poal = true;
					ch_len = br[i]->GetPos() - br[i - 1]->GetPos();//�����ԖڂƊ�Ԗڂ̒��̋����𑪂�
				}
				if (game()->GetOm()->GetBridge(i)->GetBuildS() ||
					game()->GetOm()->GetBridge(i)->GetBuildL() ||
					GetKeyboardPress(DIK_T) ||
					GetKeyboardPress(DIK_V)) {
					hit_poal = false;//������������poal�Ƃ̓����蔻��𖳂���
					use = false;
				}
			}
		}
	}
	
	if (m_pos.y > 1200 /*|| m_pos.y  < 800*/ )
		use = false;
}

//=============================================================================
// �`�揈��
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
// �e�̐�������
//=============================================================================
void BULLET::SetBullet(D3DXVECTOR2 pos, int muki,float pl_rot)
{
	Character* gp = cm->GetPlayer();
	
	if (use == false) {
		m_pos = pos;
		m_muki = muki;

		switch (m_muki) {
			case 7://������
				vel = D3DXVECTOR2(-BULLET_SPEED, -7.0f);
				vel.x += gp->speed();
				vel.y += gp->speedY();
				gravity = D3DXVECTOR2(0.3f, 0.2f);
				rot = +0.75f + pl_rot;
				rot_speed = -0.03f ;
				break;

			case 8://�E����
				vel = D3DXVECTOR2(BULLET_SPEED, -7.0f);
				vel.x += gp->speed();
				vel.y += gp->speedY();
				gravity = D3DXVECTOR2(0.3f, 0.2f);
				rot = -0.75f + pl_rot;
				rot_speed = 0.03f ;
				break;
		}
		height = 0.0f; //��őΉ�����
		hit_enemy = false;
		hit_field = false;
		hit_boss = false;
		check_ladder = false;

		//�L���t���[�����Z�b�g
		frame = 300;

		//���t���O�I��
		use = true;

		
	}
}

/*

�������[�V�����Ŕ��������������
�Ԃ������炻���ŉ��Z���~�߂ĕ\������

*/