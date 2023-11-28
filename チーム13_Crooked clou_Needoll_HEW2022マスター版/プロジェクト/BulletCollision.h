/*****************************************
 * BulletCollisionヘッダ			     *
 *針の衝突判定処理                       *
 *										 *
 *         Auther:ウチヤマ				 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"
#include "Bullet.h"
#include "Enemy_Field.h"
#include "collision.h"

	
	bool HitCheckBullet(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);

	//床
	bool HitCheckBField(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//左
	bool HitCheckBwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//右
	bool HitCheckBwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//天井
	bool HitCheckBCelling(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);

