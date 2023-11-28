/*****************************************
 * SceneChangerヘッダ					 *
 *シーンを管理するための抽象クラス       *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
class SceneChanger
{
public:
	typedef enum {
		TITLE,//タイトル画面
		SELECT,//ステージセレクト画面　宮部追加
		GAME,//ゲーム画面
		GAMEOVER,
		GAMECLEAR,
		NONE,//値なし
	}eScene;
	//virtual  ~SceneChanger()= 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定のシーンに変更する
};

