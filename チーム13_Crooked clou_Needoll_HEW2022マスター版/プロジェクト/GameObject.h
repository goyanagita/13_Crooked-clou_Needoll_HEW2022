/*********************************************
 * GameObjectヘッダ							 *
 *すべてのゲームオブジェクトはこれを継承する *
 *											 *
 *         Auther:	ミヤベ＆ウチヤマ		 *
 *         Date  :	11/04					 *
 *********************************************/
#pragma once
class GameObject
{
private:
	class Game* Game = nullptr;
public:
	
	GameObject(class Game* game);//構築時に自動的に呼ばれる
	~GameObject() ;//破棄時に自動的に呼ばれる
	void Init() {};//初期化
	void Uninit() {};//終了処理
	void Update() {};//更新処理
	void Draw() {};//描画処理

	class Game* game() { return Game; }
	
};

