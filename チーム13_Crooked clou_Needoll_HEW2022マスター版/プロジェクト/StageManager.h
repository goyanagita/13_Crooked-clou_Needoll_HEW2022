/*****************************************
 * StageManager�w�b�_					 *
 *�X�e�[�W�̊Ǘ����s���N���X             *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseStage.h"
class StageManager
{
private:
	BaseStage* NowStage = nullptr;
	BaseStage* NextStage = nullptr;

public:
	StageManager() {};
	~StageManager() {};
	void Init() {};//������
	void Uninit() {};//�I������
	void Update() {};//�X�V����
	void Draw() {};//�`�揈��
	void ChangeStage() {};//�X�e�[�W�؂�ւ��p�֐�
};

