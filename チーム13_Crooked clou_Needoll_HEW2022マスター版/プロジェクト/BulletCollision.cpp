#include "BulletCollision.h"

//=============================================================================
// íeëSëÃÇÃè’ìÀîªíËèàóù
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
//íeÇ∆ínñ ÇÃîªíËèàóù
//====================================================================

bool HitCheckBField(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//àÍÇ¬ñ⁄ÇÕämíËÇ≈íeéwíË
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
// íeÇ∆âEï«Ç∆ÇÃè’ìÀîªíËèàóù
//=============================================================================
bool HitCheckBwallleft(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//àÍÇ¬ñ⁄ÇÕämíËÇ≈íeÇéwíË
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
// íeÇ∆ç∂ï«ÇÃè’ìÀîªíËèàóù
//=============================================================================

bool HitCheckBwallright(D3DXVECTOR2 box1pos, float box1width, float box1height,
	D3DXVECTOR2 box2pos, float box2width, float box2height)
	//àÍÇ¬ñ⁄ÇÕämíËÇ≈íeÇéwíË
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
// íeÇ∆ìVà‰ÇÃè’ìÀîªíËèàóù
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
