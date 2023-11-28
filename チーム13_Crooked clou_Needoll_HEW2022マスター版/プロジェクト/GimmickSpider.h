#pragma once
#include "Character.h"

class GimmickSpider:public Character
{
private:
	struct DATA {
		D3DXVECTOR2 pos;
		bool        survFlag = 0;
	};

	DATA g_spider;


public:
	GimmickSpider(class Game* game) :Character(game) {};
	~GimmickSpider() {};
	void Init();
	void Uninit();
	void Update();
	void Draw();


};