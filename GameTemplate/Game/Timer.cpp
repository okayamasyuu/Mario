#include "stdafx.h"
#include "Timer.h"
#include "Game.h"


Timer::Timer()
{
}


Timer::~Timer()
{
	DeleteGO(m_fontRender);
}

bool Timer::Start()
{
	m_fontRender = NewGO<prefab::CFontRender>(0);
	m_fontRender->SetShadowParam(true, 2.0f, CVector4::Black);
	
	return true;
}

void Timer::Update()
{
	QueryGOs<Game>("game", [&](Game * ga)->bool {
		float zikan = ga->timer();
		float hun, byou;
		hun = zikan / 60.0f;
		byou = fmod(zikan, 60.0f);

		wchar_t text[256];
		swprintf(text, L"経過時間時間 %.f:%02.f", hun, byou);
		m_fontRender->SetText(text);

		return true;
	});

	m_fontRender->SetPosition({ 200.0f, 300.0f });
	//あ
}