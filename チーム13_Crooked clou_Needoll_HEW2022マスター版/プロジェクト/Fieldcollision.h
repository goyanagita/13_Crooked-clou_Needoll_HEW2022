/*****************************************
 * FieldCollision�w�b�_					 *
 *�n�ʂƂ̏Փ˔��菈�����s��	         *
 *										 *
 *         Auther:	(�E�`���})			 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"

//��
bool HitCheckField(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//��
bool HitCheckwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//�E
bool HitCheckwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);
//�V��
bool HitCheckCelling(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);