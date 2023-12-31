#include "BulletCollision.h"

//=============================================================================
// 弾全体の衝突判定処理
//=============================================================================
bool HitCheckBullet(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height){

	float box1Xmin = box1pos.x - (box1width / 2) ;
	float box1Xmax = box1pos.x + (box1width / 2) ;
	float box1Ymin = box1pos.y - (box1height / 2);
	float box1Ymax = box1pos.y + (box1height / 2);

	float box2Xmin = box2pos.x - (box2width / 2);
	float box2Xmax = box2pos.x + (box2width / 2);
	float box2Ymin = box2pos.y - (box2height / 2);
	float box2Ymax = box2pos.y - (box2height / 2);

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}

	return false;

}


//====================================================================
//弾と地面の判定処理
//====================================================================

bool HitCheckBField(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//一つ目は確定で弾指定
{
	float box1Xmin = box1pos.x - (box1width / 2) + 5.0f;
	float box1Xmax = box1pos.x + (box1width / 2) -5.0f;
	float box1Ymin = box1pos.y - (box1height / 2) + 4.0f;
	float box1Ymax = box1pos.y + (box1height / 2);

	float box2Xmin = box2pos.x - (box2width / 2);
	float box2Xmax = box2pos.x + (box2width / 2);
	float box2Ymin = box2pos.y - (box2height / 2);
	float box2Ymax = box2pos.y - (box2height / 2);

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}

	return false;
}

//=============================================================================
// 弾と右壁との衝突判定処理
//=============================================================================
bool HitCheckBwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//一つ目は確定で弾を指定
{
	float box1Xmin = box1pos.x - (box1width / 2)+5.0f;
	float box1Xmax = box1pos.x-5.0f;
	float box1Ymin = box1pos.y - (box1height / 2);
	float box1Ymax = box1pos.y + (box1height / 2);

	float box2Xmin = box2pos.x;
	float box2Xmax = box2pos.x + (box2width / 2);
	float box2Ymin = box2pos.y - (box2height / 2) + 5.0f;
	float box2Ymax = box2pos.y + (box2height / 2) - 5.0f;

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//=============================================================================
// 弾と左壁の衝突判定処理
//=============================================================================

bool HitCheckBwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//一つ目は確定で弾を指定
{
	float box1Xmin = box1pos.x - 2.0f;
	float box1Xmax = box1pos.x + (box1width / 2) +2.0f;
	float box1Ymin = box1pos.y - (box1height / 2);
	float box1Ymax = box1pos.y + (box1height / 2);

	float box2Xmin = box2pos.x - (box2width / 2);
	float box2Xmax = box2pos.x;
	float box2Ymin = box2pos.y - (box2height / 2) + 5.0f;
	float box2Ymax = box2pos.y + (box2height / 2) - 5.0f;

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//=============================================================================
// 弾と天井の衝突判定処理
//=============================================================================
bool HitCheckBCelling(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
{
	float box1Xmin = box1pos.x - (box1width / 2)+ 5.0f;
	float box1Xmax = box1pos.x + (box1width / 2)- 5.0f;
	float box1Ymin = box1pos.y - (box1height / 2);
	float box1Ymax = box1pos.y - (box1height / 2) + 4.0f;
	
	float box2Xmin = box2pos.x - (box2width / 2);
	float box2Xmax = box2pos.x + (box2width / 2);
	float box2Ymin = box2pos.y + (box2height / 2);
	float box2Ymax = box2pos.y + (box2height / 2) + 5.0f;

	if (box1Xmin < box2Xmax)
	{
		if (box1Xmax > box2Xmin)
		{
			if (box1Ymin < box2Ymax)
			{
				if (box1Ymax > box2Ymin)
				{
					return true;
				}
			}
		}
	}

	return false;
}
