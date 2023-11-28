/*****************************************
 * Character�w�b�_					     *
 *���ׂẴL�����N�^�[�͂�����p������   *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "GameObject.h"
#include "BaseCharacter.h"

#define PLAYER_SIZE_X (32.0f*3)
#define PLAYER_SIZE_Y (32.0f*4.5)
class Character :public GameObject
{
private:
	/*struct Character[8]:BaseCharacter*/
public:
	struct DATA
	{
		D3DXVECTOR2 pos;
		D3DXVECTOR2 vel;
		int m_TextureNo = 0;//�e�N�X�`���̎��ʎq

		float speed = 0;//�ړ����x
		float speedY = 0;
		float scale = 1;//�傫��
		float wx = 0;//����
		float wy = 0;//�c��
		float vx = 0;//���ړ���
		float vy = 0;//�c�ړ���
		int hp = 0;//�̗�
		int CharaId;//0�c�v���C�� 1�ȏ�G
		int GroupId;//0�c�����@1�c�G
		float gravityscale;
		float moveinpulse;
		bool fieldstand;
	};

	DATA Chara;
	
	Character(class Game* game);

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Create() {};
	int hp() { return Chara.hp; }
	float speed() { return Chara.speed; }
	float speedY() { return Chara.speedY; }
	int CharaId() { return Chara.CharaId; }
	int GroupId() { return Chara.GroupId; }


};

