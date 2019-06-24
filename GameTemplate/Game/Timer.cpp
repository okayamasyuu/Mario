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
	ga = FindGO<Game>(0, "game");
	return true;
}

void Timer::Update()
{
	float zikan = ga->timer();
	float hun, byou;
	hun = zikan / 60.0f;
	byou = fmod(zikan, 60.0f);

	wchar_t text[256];
	swprintf(text, L"Œo‰ßŽžŠÔŽžŠÔ %.f:%02.f", hun, byou);
	m_fontRender->SetPosition({ -600.0f, 300.0f });

	m_fontRender->SetText(text);
}