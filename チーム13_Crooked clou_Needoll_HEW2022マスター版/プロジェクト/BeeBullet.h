/*****************************************
 * BeeBullet�w�b�_				     	 *
 *�I���ł��o���e�̃N���X�@�@�@�@�@       *
 *										 *
 *         Auther:	�~���x�@�@�@�@�@	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"
#define MAX_BIRDBULLET 3	//�e�̕\���ő吔
#define BULLET_SPEED (4.0f)//�e�̑��x

class BEEBULLET:public GameObject
{
	private:
		
		struct DATA
		{
			D3DXVECTOR2 m_pos;
			D3DXVECTOR2 vel;
			int m_TextureS1 = 0;//�e�N�X�`���̎��ʎq
			int m_TextureS2 = 0;//�e�N�X�`���̎��ʎq

			float		height;	//����
			int			m_muki;	//����

			int			frame;	//�L���t���[��
			bool		use;	//���t���O
			D3DXVECTOR2 gravity;//�d��
			bool        check_eb;  //�����蔻��
		};
	
		DATA bbullet;

		class CharacterManager* cm;

	public:
		BEEBULLET(class Game* game);
		void Init();
		void Uninit();
		void Update();
		void Draw();
		void SetBeeBullet(D3DXVECTOR2 pos, int muki);
		bool GetCheckBB() { return bbullet.check_eb; }
		void SetCheckBB(bool state) { bbullet.check_eb = state; }
		bool GetUse() { return bbullet.use; }
		D3DXVECTOR2 GetBbPos(void) { return bbullet.m_pos; }
		void Delete() { bbullet.use = false; }

};

