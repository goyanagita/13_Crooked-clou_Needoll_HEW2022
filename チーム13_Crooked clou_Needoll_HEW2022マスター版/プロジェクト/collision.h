/*****************************************
 * Collisionヘッダ			             *
 *衝突判定のメイン処理			         *
 *										 *
 *         Auther:ウチヤマ				 *
 *         Date  :						 *
 *****************************************/
#pragma once

#include "main.h"

#define HIT_tate 0x00000001;
#define HIT_yoko 0x00000002
#define HIT_ue   0x00000010
#define HIT_sita 0x00000020
#define HIT_hidari 0x00000040
#define HIT_migi 0x00000080

bool HitCheckBox(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);

bool HitCheckArmField(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height);

float GetBlockHeight(void);