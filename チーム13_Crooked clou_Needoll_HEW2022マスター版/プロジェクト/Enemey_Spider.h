/*****************************************
 * Spider�w�b�_			     �@�@�@�@�@�@*
 *�G�̒w偂̃N���X(Coming Soon)�@�@�@�@�@*
 *										 *
 *         Auther:	�~���x�@�@�@�@�@	 *
 *         Date  :						 *
 *****************************************/
#pragma once	//���d��`�̋֎~

#include "main.h"
#include "renderer.h"
#include "Character.h"

//**************************************************************
//�}�N����`
//**************************************************************
#define ENEMY_MAX			(2)			//�t�B�[���h�@�ő吔
#define ENEMY_SIZE			(64.0f)		//�t�B�[���h�@�T�C�Y



//**************************************************************
//�\����
//**************************************************************
class Enemy :public Character
{
protected:
	enum Enemy_state {
		STS_NULL = 0,
		STS_SPAWN,
		STS_NORMAL,
	};

	struct DATA
	{
		bool		useFg;
		int			status;	
	};
	
	DATA enemy;


public:
	Enemy(class Game* game) :Character(game) {}
	~Enemy() {};

	virtual void Init() = 0;//������
	virtual void Uninit() = 0;//�I������
	virtual void Update() = 0;//�X�V����
	virtual void Draw() = 0;//�`�揈��
	bool Collision(D3DXVECTOR2 pos);


	//�Q�b�^�[
	D3DXVECTOR2	GetPos() { return Chara.pos; }
	bool		GetUse() { return enemy.useFg; }
	int			GetStatus() { return enemy.status; }

};

class Spider : public Enemy {
private:
	struct DATA
	{
		float		posStart;
		float		posSpawn;
	};
	const float m_AnimTbl[5] =
	{
		0.0f,
		0.25f,
		0.5f,
		0.75f,
		0.0f
	};
	DATA spider;
	//D3DXVECTOR2 pos;
public:
	Spider(class Game* game, D3DXVECTOR2 pos);
	
	void Init()override;//������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	//void Init(void);//������
	//void Uninit(void);//�I������
	//void Update(void);//�X�V����
	//void Draw(void);//�`�揈��

	//�X�V����
	void Update_Null(D3DXVECTOR2 PlayerPos);
	void Update_Spawn(D3DXVECTOR2 PlayerPos);
	void Update_Back(D3DXVECTOR2 PlayerPos);


	//�X�e�[�^�X�ύX�֐�
	void ChangeStatus(Enemy_state state) { enemy.status = state; }
};
