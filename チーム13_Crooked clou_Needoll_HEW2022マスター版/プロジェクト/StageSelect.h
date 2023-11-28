/*****************************************
 * StageSelectヘッダ					 *
 *ステージの管理を行うクラス             *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "BaseScene.h"
#include "main.h"

class StageSelect :public BaseScene
{
private:
	int m_texture_selectbg;
	int  m_texture_1st;//ステージ1
	int  m_texture_2nd;//ステージ2
	int  m_texture_3rd;//ステージ3
	int  m_texture_4th;//ステージ4
	int  m_texture_5th;//ステージ5
	int m_texture_player;

	int m_SENo;

	D3DXVECTOR2 pos_slctbg;
	D3DXVECTOR2 pos_1st;
	D3DXVECTOR2 pos_2nd;
	D3DXVECTOR2 pos_3rd;
	D3DXVECTOR2 pos_4th;
	D3DXVECTOR2 pos_5th;
	D3DXVECTOR2 pos_player;


	bool  flag_first = false;//ステージクリアしたらtrueにする
	bool  flag_second = false;//ステージクリアしたらtrueにする
	bool  flag_third = false;//ステージクリアしたらtrueにする
	bool  flag_fourth = false;//ステージクリアしたらtrueにする
	bool  flag_fifth = false;//ステージクリアしたらtrueにする

	int stg_select = 0;
	int CC = 0; //解放チェック　ステージクリアごとに+1する

	int	stage_now;
	bool exit = false;

	bool goal_check = false;

	float frame = 0; 
	enum {
		STG_1st,//0
		STG_2nd,//1
		STG_3rd,//2
		STG_4th,//3
		STG_5th,//4

		STG_MAX,
	};

public:
	StageSelect(SceneChanger* changer) :BaseScene(changer) {};//構築時に自動的に呼ばれる
	~StageSelect() {};//破棄時に自動的に呼ばれる
	void Init();//初期化
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	int GetStage(void) { return stg_select; }
	void SetClear(void) { goal_check = true; }
	void SetStageInfo(int stage) 
	{ 
		stg_select = stage; 
		CC = stage; 
		stage_now = stage;
		switch (stage) {
		case 0:
			pos_player = D3DXVECTOR2(pos_1st.x, pos_1st.y - 90.0f);;
			break;
		case 1:
			pos_player = pos_2nd;
			pos_player.x += 50;
			flag_first = true;
			break;
		case 2:
			pos_player = pos_3rd;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			break;
		case 3:
			pos_player = pos_4th;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			flag_third = true;
			break;
		case 4:
			pos_player = pos_5th;
			pos_player.x += 50;
			flag_first = true;
			flag_second = true;
			flag_third = true;
			flag_fourth = true;
			break;

		}
	}
};
