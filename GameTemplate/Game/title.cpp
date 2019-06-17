#include "stdafx.h"
#include "title.h"
#include "Game.h"

title::title()
{
}


title::~title()
{
	DeleteGO(m_spriteRender);
}
bool title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Mario.Title.dds", 700, 350);
	return true;
}
void title::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}