/*****************************************
 * BasCharacterヘッダ					 *
 *すべてのキャラクターはこれを継承する   *
 *										 *
 *         Auther:	ミヤベ＆ウチヤマ	 *
 *         Date  :						 *
 *****************************************/
#pragma once
#include "main.h"
#include "sprite.h"
#include "texture.h"

class BaseCharacter
{
public:
	BaseCharacter() {};//オブジェクト構築のタイミングで自動的に呼びだされる
	~BaseCharacter() {};//オブジェクト破棄のタイミング自動的に呼び出される
	void Init() {};//初期化
	void Uninit() {};//終了処理
	void Update() {};//更新処理
	void Draw() {};//描画処理

};

