/*****************************************
 * BasScene�w�b�_			     		 *
 *���ׂẴV�[���͂�����p������ �@�@�@  *
 *										 *
 *         Auther:�~���x���E�`���}		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "SceneChanger.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
class BaseScene
{
protected:
	
	SceneChanger* m_SceneChanger= nullptr;
public:
	BaseScene(SceneChanger* changer);//�I�u�W�F�N�g�\�z�̃^�C�~���O�Ŏ����I�ɌĂт������
	~BaseScene() {};//�I�u�W�F�N�g�j���̃^�C�~���O�����I�ɌĂяo�����
	virtual void Init() {};//�V�[���̏�����
	virtual void Uninit() {};//�V�[���̏I������
	virtual void Update() {};//�V�[���̍X�V����
	virtual void Draw() {};//�V�[���̕`�揈��
	virtual bool ErrorCheck(void) { return false; };
	virtual bool ExitCheck(void) { return false; }
	virtual void  SetStageInfo(int stage) {};
	virtual int GetStage(void) { return -1; };
	virtual bool CheckClear(void) { return false; }
	virtual void SetClear(void) {}
};

