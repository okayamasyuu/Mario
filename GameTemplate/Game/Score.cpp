#include "stdafx.h"
#include "Score.h"


Score::Score()
{
}


Score::~Score()
{
	DeleteGO(font);
}
bool Score::Start()
{
	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Black);
	return true;
}
void Score::Update()
{
	wchar_t text[256];
	swprintf(text, L"%04d　スコア", Count);
	font->SetText(text);
	font->SetPosition({ 360.0f, 200.0f }); //位置
}
