/*****************************************
 * Bullet�w�b�_					         *
 *�v���C���[�̔��˂���j�̃N���X         *
 *										 *
 *         Auther:		�E�`���}		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "main.h"
#include "Character.h"

#define MAX_BULLET 1	//�e�̕\���ő吔
#define BULLET_SPEED (6.0f)//�e�̑��x

class BULLET :public GameObject {
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 vel;
	int m_TextureNo = 0;//�e�N�X�`���̎��ʎq

	float		height;	//����
	int			m_muki;	//����

	int			frame;	//�L���t���[��
	int			use;	//���t���O
	D3DXVECTOR2 gravity;//�d��
	bool        check;  //�����蔻��

	bool		check_ladder;
	bool		hit_field = false;//�n�ʂƂ̏Փ˔���
	bool		hit_enemy = false;
	bool		hit_boss = false;

	float rot;			//��]�p�x
	float rot_speed;	//��]�X�s�[�h
	class CharacterManager* cm;//�L�����N�^�[�}�l�[�W���[�|�C���^

		//�{���ǉ�
	class ObjectManager* om;//�I�u�W�F�N�g�}�l�[�W���[�|�C���^
	bool        hit_poal = false;//���̒��Ƃ̓����蔻��
	D3DXVECTOR2 ch_len;
	int			SENo;


public:



	BULLET(class Game* game);
	~BULLET() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetBullet(D3DXVECTOR2 pos, int muki, float pl_rot);//�e�̃Z�b�^�[
	//�e�Q�b�^�[
	bool GetCheck() { return check; }
	bool GetCheckLadder() { return check_ladder; }
	bool GetHitField() { return hit_field; }
	bool GetHitEnemy(void) { return hit_enemy; }
	bool GetUse(void) { return use; }
	float GetFrame() { return frame; }
	float GetRot(void) { return rot; }
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	bool GetHitBoss(void) { return hit_boss; }

	bool GetHit(void) {
		if (GetHitBoss() || GetHitEnemy())
			return true;
		else
			return false;
	}

	//�{���ǉ�
	D3DXVECTOR2 GetLen() { return ch_len; }
	bool GetHitPoal(void) { return hit_poal; }

	//�ʂ̃Z�b�^�[
	void SetCheck(bool state) { check = state; }
	void SetUse(bool state) { use = state; }
	void SetHitField(bool state) { hit_field = state; }
	void SetVelX(void) { vel.x *= -1; /*vel.x /= 2;*/ }
	void SetVelY(void) { vel.y *= -1; /*vel.y /= 2;*/ }
	void SetPos(D3DXVECTOR2 pos) { m_pos += (pos * 10.0f); }
	void SetCheckLadder(bool state) { check_ladder = state; }
	void SetHitBoss(bool hit) { hit_boss = hit; }



};

