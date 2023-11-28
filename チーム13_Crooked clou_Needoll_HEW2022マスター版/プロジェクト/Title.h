/*****************************************
 * Titleヘッダ							 *
 *タイトルシーンの管理を行うクラス       *
 *										 *
 *         Auther:	ウチヤマ			 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseScene.h"
#include "main.h"

#define MOVE_SPEED 5.0f
#define MOVE_UP   0.6f
class Title :public BaseScene
{
private:
	int  m_texture_bg;		//最背面背景
	int  m_texture_new;	    //ニューゲーム
	int  m_texture_load;	//ロード
	int  m_texture_op;		//オプション
	int  m_texture_exit;	//終了
	int  m_texture_title;    //タイトル  宮部追加

	int  m_BGMNo;
	int  m_SENo;
	int  m_SENo2;

	D3DXVECTOR2 pos_new;
	D3DXVECTOR2 pos_load;
	D3DXVECTOR2 pos_op;
	D3DXVECTOR2 pos_exit;
	D3DXVECTOR2 pos_title;//宮部追加

	D3DXVECTOR2 pos_new_first;
	D3DXVECTOR2 pos_load_first;
	D3DXVECTOR2 pos_op_first;
	D3DXVECTOR2 pos_exit_first;


	D3DXVECTOR2 vel_new;
	D3DXVECTOR2 vel_load;
	D3DXVECTOR2 vel_op;
	D3DXVECTOR2 vel_exit;

	int select_menu = 2;
	float frame = 0;
	bool exit = false;

	bool flag_new = false;
	bool flag_load = false;
	bool flag_op = false;
	bool flag_exit = false;

	class Option* op = nullptr;

	enum {
		MODE_EXIT,
		MODE_LOAD,
		MODE_NEW,
		MODE_OP,		
		

		MODE_MAX,

	};

public:
	Title(SceneChanger* changer) :BaseScene(changer) {};//構築時に自動的に呼ばれる
	~Title() {};//破棄時に自動的に呼ばれる
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理

	void ResetPosNew(void) { if (pos_new.y < pos_new_first.y)pos_new.y += MOVE_SPEED; };
	void ResetPosLoad(void) { if (pos_load.y < pos_load_first.y)pos_load.y += MOVE_SPEED; };
	void ResetPosOp(void) { if (pos_op.y < pos_op_first.y)pos_op.y += MOVE_SPEED; };
	void ResetPosExit(void) { if (pos_exit.y < pos_exit_first.y)pos_exit.y += MOVE_SPEED; };

	bool ExitCheck(void) { return exit; }
};

