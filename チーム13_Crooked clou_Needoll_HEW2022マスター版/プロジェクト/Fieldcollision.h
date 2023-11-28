/*****************************************
 * FieldCollisionヘッダ					 *
 *地面との衝突判定処理を行う	         *
 *										 *
 *         Auther:	(ウチヤマ)			 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"

//床
bool HitCheckField(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//左
bool HitCheckwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//右
bool HitCheckwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//天井
bool HitCheckCelling(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);