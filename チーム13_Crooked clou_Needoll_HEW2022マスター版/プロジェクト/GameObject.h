/*********************************************
 * GameObject�w�b�_							 *
 *���ׂẴQ�[���I�u�W�F�N�g�͂�����p������ *
 *											 *
 *         Auther:	�~���x���E�`���}		 *
 *         Date  :	11/04					 *
 *********************************************/
#pragma once
class GameObject
{
private:
	class Game* Game = nullptr;
public:
	
	GameObject(class Game* game);//�\�z���Ɏ����I�ɌĂ΂��
	~GameObject() ;//�j�����Ɏ����I�ɌĂ΂��
	void Init() {};//������
	void Uninit() {};//�I������
	void Update() {};//�X�V����
	void Draw() {};//�`�揈��

	class Game* game() { return Game; }
	
};

