/*****************************************
 * BulletCollision�w�b�_			     *
 *�j�̏Փ˔��菈��                       *
 *										 *
 *         Auther:�E�`���}				 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"
#include "Bullet.h"
#include "Enemy_Field.h"
#include "collision.h"

	
	bool HitCheckBullet(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);

	//��
	bool HitCheckBField(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//��
	bool HitCheckBwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//�E
	bool HitCheckBwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);
	//�V��
	bool HitCheckBCelling(D3DXVECTOR2 box1pos, float box1width, float box1height,
		D3DXVECTOR2 box2pos, float box2width, float box2height);

