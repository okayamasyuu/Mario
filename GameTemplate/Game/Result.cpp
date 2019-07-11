#include "stdafx.h"
#include "Result.h"
#include "title.h"
#include "Timer.h"

Result::Result()
{
}


Result::~Result()
{
	DeleteGO(m_resultSprite);
	DeleteGO("ŽžŠÔ");
	DeleteGO(m_fontRender);
}
bool Result::Start()
{
	m_resultSprite = NewGO<prefab::CSpriteRender>(0);
	m_resultSprite->Init(L"sprite/result.dds", 1280.0f, 720.0f);//ƒŠƒUƒ‹ƒg‰æ–Ê
	m_fontRender = NewGO<prefab::CFontRender>(0);
	m_fontRender->SetShadowParam(true, 2.0f, CVector4::Black);
	time = FindGO<Timer>("ŽžŠÔ");
	return true;
}
void Result::Update()
{
	float hunRe, byouRe;
	hunRe = time->hun;
	byouRe = time->byou;
	wchar_t zikan[256];
	swprintf(zikan, L" %.f:%02.f", hunRe, byouRe);
	m_fontRender->SetText(zikan);
	
	if (Pad(0).IsPress(enButtonA) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}
}
