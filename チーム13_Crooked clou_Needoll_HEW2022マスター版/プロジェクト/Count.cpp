#include "Count.h"

int g_count;
int g_countB;
bool count_start;
bool countB_start;

void InitCount()
{
	g_count = 0;//普通にカウント
	count_start = true;//宮部変更
}

void UninitCount()
{

}

void UpdateCount()
{
	if (count_start == true)
	{
		g_count += 1.0;//1秒＝60フレーム
	}

	if (countB_start == true)
	{
		g_countB += 1.0;
	}
}

float GetCount()
{
	return (g_count / 60);//大体[秒]で出る
}

float GetCountB()
{
	return g_countB / 60;
}

int GetFrame()
{
	return g_count;//フレームで出せる
}

int GetFrameB()
{
	return g_countB;
}

void ResetCount()
{
	g_count = 0;
}

void BossReset()
{
	g_countB = 0;
}

void Start()
{
	count_start = true;
}

void Stop()
{
	count_start = false;
}

void StartB()
{
	countB_start = true;
}

void StopB()
{
	countB_start = false;
}
