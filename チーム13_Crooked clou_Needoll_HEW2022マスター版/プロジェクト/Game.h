/*****************************************
 * Game�w�b�_							 *
 *�Q�[���V�[���̊Ǘ����s���N���X         *
 *										 *
 *         Auther:�~���x���E�`���}		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseScene.h"
#include "sprite.h"
#include "texture.h"

#define MAP_WIDTH  60
#define MAP_HEIGHT 20
#define MAPCHIP 32.0f
class Game:public BaseScene
{
private:
	class MAP* Map = nullptr;
	class CharacterManager* cm = nullptr;
	class BULLET* bullet = nullptr;
	class CAMERA_2D* camera = nullptr;
	class BackGround* bg = nullptr;
	class ObjectManager* om = nullptr;
	class ThreadGauge* tg = nullptr;
	class Pause*	pause = nullptr;
	class Life* life = nullptr;
	bool error  = false;
	bool goal = false;
	int m_stage = 0;

	//�{���ǉ�----------------------------
	class ENEMYBULLET* ebullet = nullptr;
	class BEEBULLET* bbullet = nullptr;
	class BLOCK* block = nullptr;
	class Bridge* bridge = nullptr;//1/8�ǉ�
	//------------------------------------

public:
	Game(SceneChanger* changer):BaseScene(changer){};
	~Game() {};
	void Init() override;//������
	void Uninit() override;//�I������
	void Update()override ;//�X�V����
	void Draw()override;//�`�揈��

	class MAP* map() { return Map; }
	class BULLET* GetBullet() { return bullet; }
	class CharacterManager* GetCm() { return cm; }
	
	class CAMERA_2D* GetCamera() { return camera; }
	class ObjectManager* GetOm(void) { return om; }
	class ThreadGauge* GetTg(void) { return tg; }

	//�{���ǉ�-------------------------------------------------------
	class ENEMYBULLET* GetEnemyBullet() { return ebullet; }
	class BEEBULLET* GetBeeBullet() { return bbullet; }
	class BLOCK* GetBlock() { return block; }
	//----------------------------------------------------------------

	bool ErrorCheck(void) { return error; }

	bool CheckClear(void) { return goal; }
	void SetGoal(bool state) { goal = state; }
	void  SetStageInfo(int stage) { m_stage = stage; };
	int GetStage(void) { return m_stage; }
};

