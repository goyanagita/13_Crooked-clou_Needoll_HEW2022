/*****************************************
 * SceneChanger�w�b�_					 *
 *�V�[�����Ǘ����邽�߂̒��ۃN���X       *
 *										 *
 *         Auther:	�~���x���E�`���}	 *
 *         Date  :						 *
 *****************************************/
#pragma once
class SceneChanger
{
public:
	typedef enum {
		TITLE,//�^�C�g�����
		SELECT,//�X�e�[�W�Z���N�g��ʁ@�{���ǉ�
		GAME,//�Q�[�����
		GAMEOVER,
		GAMECLEAR,
		NONE,//�l�Ȃ�
	}eScene;
	//virtual  ~SceneChanger()= 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��̃V�[���ɕύX����
};

