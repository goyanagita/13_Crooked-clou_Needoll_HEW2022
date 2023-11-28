/*****************************************
 * CharacterManager�w�b�_			     *
 *�L�����N�^�[�̊Ǘ����s���N���X         *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "Character.h"
#include "Player.h"
#include "GameObject.h"

#define ENEMY_FIELD_MAX 20
#define ENEMY_SPIDER_MAX (2)			//�t�B�[���h�@�ő吔

 //�{���ǉ�------------------------
#define BIRD_MAX 100
#define BEE_MAX 100
#define E_BULLET 100
#define B_BULLET 100


class CharacterManager:public GameObject
{
private:

	struct DATA {
		int numPlayer = 0;//�v���C���[
		int numPlayerBullet = 0;//�j
		int numEnemy_Field = 0;//�n��G
		//int numEnemy_Air = 0;//�󒆓G
		//int numEnemy_AirBullet = 0;//�󒆓G�̒e
		
	};

	int Total = 0;
	int total_enemy_f = 0;
	int total_enemy_w = 0;//�Ƃ�//�{���ǉ�
	int total_enemy_s = 0;//�͂�
	int total_spider = 0;
	float hit_frame = 0;
	class Character** Characters = nullptr;
	class Player* player = nullptr;
	class BOSS* boss = nullptr;
	Character* Enemy = nullptr;
	int m_SENo;


protected:
	class Enemy_Field* f_Enemy[ENEMY_FIELD_MAX];
	class Spider* spider[ENEMY_SPIDER_MAX];
	class Enemy_Bird* f_Bird[BIRD_MAX];	//�{���ǉ�
	class Enemy_Bee* f_Bee[BEE_MAX];
public:
	CharacterManager(class Game* game);
	~CharacterManager();
	void create(int ID,D3DXVECTOR2 pos);
	void appear(char charaId, float wx, float wy, float vx = 0, float vy = 0) {};
	void Init();
	void Uninit();
	void Update() ;
	void Draw();
	int GetEnemyfTotal(void){ return total_enemy_f; }
	class Player* GetPlayer();
	class Enemy_Field* GetEnemyField(int i);
	class BOSS* GetBoss();
	void SubTotal(void) { total_enemy_f--; }
	void HitCharacter(void);

	//�{���ǉ�
	class Enemy_Bird* GetBird(int i);
	class Enemy_Bee* GetBee(int i);
	int GetEnemywTotal(void) { return total_enemy_w; }
	int GetEnemysTotal(void) { return total_enemy_s; }
};

