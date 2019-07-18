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
		//float hun, byou;
		hun = zikan / 60.0f;
		byou = fmod(zikan, 60.0f);
		wchar_t text[256];
		//swprintf(text, L"%.f:%02.fŒo‰ß", hun, byou);
		m_fontRender->SetText(text);

		return true;
	});

	m_fontRender->SetPosition({ 400.0f, 300.0f });
}