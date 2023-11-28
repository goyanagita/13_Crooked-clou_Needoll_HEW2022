/*****************************************
 * EnemyBullet�w�b�_					 *
 *���̔��˂���H���̃N���X        �@�@�@ *
 *										 *
 *         Auther:		�~���x		 �@�@*
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"
#define MAX_BIRDBULLET 2	//�e�̕\���ő吔
#define BULLET_SPEED (4.0f)//�e�̑��x

class ENEMYBULLET:public GameObject
{
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	int m_TextureF1 = 0;//�e�N�X�`���̎��ʎq
	int m_TextureF2 = 0;//�e�N�X�`���̎��ʎq

	float		height;	//����
	int			m_muki;	//����

	int			frame;	//�L���t���[��
	bool		use;	//���t���O
	D3DXVECTOR2 gravity;//�d��
	bool        check_eb;  //�����蔻��

	class CharacterManager* cm;
	class BLOCK * bl;
	class Enemy_Bird* eb;

	
public:
	ENEMYBULLET(class Game* game);
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetEnemyBullet(D3DXVECTOR2 pos, int muki);
	bool GetCheckEB() { return check_eb; }
	void SetCheckEB(bool state) { check_eb = state; }
	bool GetUse(void) { return use; }
	D3DXVECTOR2 GetEbPos(void) { return m_pos; }
	void Delete() { use = false; }

};

