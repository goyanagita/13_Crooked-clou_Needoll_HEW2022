#pragma once
/*********************************************
 * Bridge�w�b�_								 *
 *����\������N���X						 *
 *										     *
 *         Author:�~���x�@�@�@�@�@�@		 *
 *         Date  :1/08					     *
 *********************************************/

#include "GameObject.h"
#include "input.h"
#include "inputx.h"
#include "Bullet.h"
#include "Game.h"

class Bridge : public GameObject {
private:
	int AnimPtn = 0;
	int AnimCounter;
	int m_TexturePo1 = 0;//�e�N�X�`���̎��ʎq
	int m_TextureBr1 = 0;//�e�N�X�`���̎��ʎq
	int m_TextureBr2 = 0;//�e�N�X�`���̎��ʎq
	int m_SENo;
	D3DXVECTOR2 m_pos;

	BULLET* pBullet = game()->GetBullet();

	float posx;
	int save_flag;
	int use;

	bool build_s = false;
	bool build_l = false;
	int state;
	bool hit;
	
public:
	Bridge(class Game* game, D3DXVECTOR2 pos);
	~Bridge() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetHit(bool bhit) { hit = bhit; }
	bool GetBuildS() { return build_s; }
	bool GetBuildL() { return build_l; }
	int GetAnim() { return AnimPtn; }

	D3DXVECTOR2 GetPos(void) { return m_pos; }

};


/*


1.��肽������
�����h��������j�������ŉ������

2.��Q������
��������������������@�\������狴�͏�ɗ��������Ă��邩��j�͔��˂���Ȃ��Ȃ�

3.���{
���{�͏����������傫���������������S�������蔻�蔭�������Ⴄ











*/