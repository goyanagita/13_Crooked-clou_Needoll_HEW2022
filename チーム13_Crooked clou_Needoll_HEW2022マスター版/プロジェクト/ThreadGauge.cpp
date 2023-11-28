#include "ThreadGauge.h"
#include "texture.h"
#include "sprite.h"

#define DIVIDE_X 6	//‰¡‚Ì•ªŠ„”
#define DIVIDE_Y 1	//c‚Ì•ªŠ„”

#define PATTERN_WIDTH (1.0f / DIVIDE_X)
#define PATTERN_HEIGHT (1.0f / DIVIDE_Y)

static float g_AnimeTable[6] =
{
	0.0f,
	0.16666666f,
	0.16666666f*2,
	0.16666666f*3,
	0.16666666f*4,
	0.16666666f*5,
};
int g_test = 0;
float g_count = 0;
ThreadGauge::ThreadGauge(class Game * game):GameObject(game)
{
}

void ThreadGauge::Init(void)
{

	m_texture_no = LoadTexture((char*)"data/TEXTURE/string_gauge.png");
	thread_cap = thread_cap_max;
	m_pos = D3DXVECTOR2(32.0f, 32.0f);
	view_gauge = 0;
}

void ThreadGauge::Uninit(void)
{
}

void ThreadGauge::Update(void)
{
	if (thread_cap >= 100)
		thread_cap = 100;
	if (thread_cap <= 0)
		thread_cap = 0;

	if (thread_cap >= 81)
		view_gauge = 0;
	if (thread_cap >= 61 && thread_cap < 81)
		view_gauge = 1;
	if (thread_cap >= 41 && thread_cap < 61)
		view_gauge = 2;
	if (thread_cap >= 21 && thread_cap < 41)
		view_gauge = 3;
	if (thread_cap >= 1 && thread_cap < 21)
		view_gauge = 4;
	if (thread_cap == 0)
		view_gauge = 5;
}

void ThreadGauge::Draw(void)
{
	DrawSprite(m_texture_no, m_pos.x, m_pos.y, 64.0f, 64.0f , g_AnimeTable[view_gauge], 0.0f, PATTERN_WIDTH, PATTERN_HEIGHT);
}


/*

100`81:‚È‚É‚à‚µ‚È‚¢5

80`61:Ÿ‚ÌêŠ‚ÉˆÚ‚·4

60`41:Ÿ‚ÌêŠ‚ÉˆÚ‚·3

40`21:Ÿ‚ÌêŠ‚ÉˆÚ‚·2

21`1:Ÿ‚ÌêŠ‚ÉˆÚ‚·1

0:Ÿ‚ÌêŠ‚ÉˆÚ‚·0



*/