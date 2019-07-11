#include "stdafx.h"
#include "Result.h"
#include "title.h"
#include "Timer.h"
#include "Score.h"

Result::Result()
{
}


Result::~Result()
{
	DeleteGO(m_resultSprite);
	//DeleteGO("時間");
	DeleteGO(m_fontRender);
	DeleteGO(font);
}
bool Result::Start()
{
	m_resultSprite = NewGO<prefab::CSpriteRender>(0);
	m_resultSprite->Init(L"sprite/result.dds", 1280.0f, 720.0f);//リザルト画面
	m_fontRender = NewGO<prefab::CFontRender>(0);
	m_fontRender->SetShadowParam(true, 2.0f, CVector4::Gray);
	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Gray);
	
	//time = FindGO<Timer>("時間");
	////float hunRe, byouRe;
	//hunRe = time->hun;
	//byouRe = time->byou;

	//sc = FindGO<Score>("スコア");
	////float count;
	//count = sc->Count;

	return true;
}
void Result::Update()
{
	/*float hunRe, byouRe;
	hunRe = time->hun;
	byouRe = time->byou;*/
	wchar_t zikan[256];
	/*TK_LOG("hunRe = %f\n", hunRe);
	TK_LOG("byouRe = %f\n", byouRe);*/
	swprintf(zikan, L" %d分%0.2f秒", (int)hunRe, byouRe);
	m_fontRender->SetText(zikan);
	
	wchar_t text[256];
	/*float count;
	count = sc->Count;*/
	swprintf(text, L"%04d", count);
	font->SetText(text);

	if (Pad(0).IsPress(enButtonA) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}

	m_fontRender->SetPosition({ 0.0f, -200.0f });
	m_fontRender->SetScale(2);
	font->SetPosition({ 150.0f, 70.0f });
	font->SetScale(3);
}