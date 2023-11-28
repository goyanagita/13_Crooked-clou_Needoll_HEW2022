#include "Option.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "inputx.h"

void Option::Init()
{
	m_textrue_no = LoadTexture((char*)"data/TEXTURE/option_.png");
	m_pos = D3DXVECTOR2(SCREEN_WIDTH / 2, -(SCREEN_HEIGHT / 2));
	m_pos_purpose = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_pos_init = m_pos;
	m_vel = D3DXVECTOR2(0.0f, 0.0f);
}

void Option::Uninit()
{
	if (m_pos != m_pos_init) {
		D3DXVECTOR2 move = m_pos_init - m_pos;
		D3DXVec2Normalize(&move, &move);
		m_vel += (move * 1.0f);
		m_pos += m_vel; 
		D3DXVECTOR2 vDist;
		vDist = m_pos_init - m_pos;

		float len = D3DXVec2Length(&vDist);
		if (len < 15.0f) {
			m_pos = m_pos_init;
			finish = true;
		}
		
	}
}

void Option::Update()
{
	if (m_pos != m_pos_purpose) {

		D3DXVECTOR2 move = m_pos_purpose - m_pos;
		D3DXVec2Normalize(&move, &move);
		m_vel += (move * 0.5f);
		m_pos += m_vel;

		D3DXVECTOR2 vDist;
		vDist = m_pos - m_pos_purpose;

		float len = D3DXVec2Length(&vDist);
		if (len < 1.5f) {
			m_pos = m_pos_purpose;
			m_vel = D3DXVECTOR2(0.0f, 0.0f);
		}
	}
	else {
		//“ü—Í‚Åƒƒjƒ…[—“‚ð•ÏX

		if (GetKeyboardTrigger(DIK_F)) {
			exit_option = true;
		}
	}
}

void Option::Draw()
{
	DrawSprite(m_textrue_no, m_pos.x, m_pos.y, 721, 549, 0.0f, 0.0f, 1.0f, 1.0f);
}
