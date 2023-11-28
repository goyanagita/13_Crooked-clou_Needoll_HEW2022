//�I�̓G----------------------------------------------------------------------
//���E�ɓ����@�e�o��
//�쐬�ҁ@Masaya Miyabe
//----------------------------------------------------------------------------

#include "Enemy_Bee.h"
#include "GameObject.h"
#include "Game.h"
#include "Character.h"
#include "CharacterManager.h"
#include "texture.h"
#include "sprite.h"
#include "Camera.h"
#include "Count.h"
#include "Player.h"
#include "Beebullet.h"

#define DIVIDE_X 8
#define DIVIDE_Y 4
#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static float g_MukiTbl[4]
{
	0.0f,
	0.25f,
	0.5f,
	0.75f
};

void Enemy_Bee::Init()
{
	Chara.m_TextureNo = LoadTexture((char*)"data/TEXTURE/�I4.png");
	f_bee.m_TextureNo2 = LoadTexture((char*)"data/TEXTURE/deathbee.png");
	Chara.vel = D3DXVECTOR2(0.8f, 1.0f);
	f_bee.AnimPtn = 0;
	f_bee.survFlag = true;//0�Ȃ玀�S
	f_bee.muki = 0;
	ebb = game()->GetBeeBullet();
	Chara.hp = 3;
}

void Enemy_Bee::Update()
{
	

	//�ړ�����
	//��Βl
	//�ʂ̒l�ɓ���Ē�������ύX
	int gc = GetCount();


	if (f_bee.survFlag == 1)//�����Ă��瓮����
	{	
		MoveBee();

		//�v���C���[��������荶�ɂ����獶���E�ɂ�����E������
		D3DXVECTOR2 plpos = game()->GetCm()->GetPlayer()->GetPlayerPos();
		if (plpos.x > Chara.pos.x)//��
		{
			f_bee.muki = 1;
		}
		else if (plpos.x < Chara.pos.x)//�E
		{
			f_bee.muki = 0;
		}

		//�U������
		if (gc % 11 == 0)
		{
			ebb->SetBeeBullet(D3DXVECTOR2(Chara.pos.x, Chara.pos.y), f_bee.muki);

			f_bee.AnimPtn = 1;//���o���̎��ɂ�������
		}
	}

	f_bee.AnimCounter++;


	if (f_bee.survFlag == false && f_bee.AnimCounter >= 10)
	{
		gc = 1;
		f_bee.AnimCounter = 0;
		if (f_bee.DeathPtn < 9)
			f_bee.DeathPtn++;

		if (f_bee.DeathPtn >= 9)
			f_bee.DeathPtn = 9;

	}
}


void Enemy_Bee::MoveBee()
{
	D3DXVECTOR2 campos = game()->GetCamera()->GetPos();

	Chara.pos.x -= Chara.vel.x;
	Chara.pos.y -= Chara.vel.y;
	f_bee.MoveRangeX += Chara.vel.x;
	f_bee.MoveRangeY += Chara.vel.y;

	if (fabs(f_bee.MoveRangeX) >= 400)
	{
		Chara.vel.x *= -1;
		f_bee.muki = 1;
		f_bee.MoveRangeX = 0;
	}

	if (fabs(f_bee.MoveRangeY) >= 60)
	{
		f_bee.muki = 0;
		Chara.vel.y *= -1;
		f_bee.MoveRangeY = 0;
	}

	if (f_bee.AnimCounter > 40) {
		f_bee.AnimPtn++;
		if (f_bee.AnimPtn >= 8) {
			f_bee.AnimPtn = 0;
		}
		f_bee.AnimCounter = 0;
	}

	if (Chara.hp == 0)
		f_bee.survFlag = 0;


}

void Enemy_Bee::Draw()
{
	D3DXVECTOR2 basePos = game()->GetCamera()->GetBase();
	BULLET* bl[MAX_BULLET];

	for (int i = 0; i < MAX_BULLET; i++)
		bl[i] = game()->GetBullet();


	if (f_bee.survFlag == 1)
	{
		DrawSpriteColor(Chara.m_TextureNo,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			128.0f, 128.0f,
			m_AnimTbl[f_bee.AnimPtn], g_MukiTbl[f_bee.muki],
			PATTERN_WIDTH,
			PATTERN_HEIGHT,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}


	if (f_bee.survFlag == 0)
	{
		DrawSpriteColor(f_bee.m_TextureNo2,
			basePos.x + Chara.pos.x,
			basePos.y + Chara.pos.y,
			220.0f, 220.0f,
			m_DeathTbl[f_bee.DeathPtn], 0.0,
			0.1f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

