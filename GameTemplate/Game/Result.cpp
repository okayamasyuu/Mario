#include "stdafx.h"
#include "Result.h"
#include "title.h"

Result::Result()
{
}


Result::~Result()
{
	DeleteGO(m_resultSprite);
}
bool Result::Start()
{
	m_resultSprite = NewGO<prefab::CSpriteRender>(0);
	//m_resultSprite->Init(L"sprite/banana.dds", 500, 200);//ƒŠƒUƒ‹ƒg‰æ–Ê
	return true;
}
void Result::Update()
{
	if (Pad(0).IsPress(enButtonA) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}
}
