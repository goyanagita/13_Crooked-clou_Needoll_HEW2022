/*****************************************
 * Optionヘッダ							 *
 *オプション画面の管理を行うクラス		 *
 *										 *
 *         Auther:		ウチヤマ		 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"

class Option
{
private:
	int m_textrue_no;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_vel;
	D3DXVECTOR2 m_pos_purpose;
	D3DXVECTOR2 m_pos_init;

	int select_option = 0;

	bool exit_option = false;
	bool finish = false;
public:

	Option() {};
	~Option() {};
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理

	bool GetExitOption(void) { return exit_option; }
	
	bool GetFinish(void) { return finish; }
};


