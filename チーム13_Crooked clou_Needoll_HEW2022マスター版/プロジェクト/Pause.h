/*****************************************
 * Pauseヘッダ							 *
 *ポーズ画面の管理を行うクラス			 *
 *										 *
 *         Auther:	ウチヤマ		     *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"

class Pause
{
private:
	int m_textrue_no;
	D3DXVECTOR2 m_pos;


	int select_menu = 0;

	bool exit_menu = false;
public:
	
	Pause() {};
	~Pause() {};
	void Init()	;//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw()	;//描画処理

	bool GetExitMenu(void) { return exit_menu; }
};

