#include "stdafx.h"
#include "title.h"
#include "Game.h"

title::title()
{
}


title::~title()
{
}
bool title::Start()
{
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/.dds", 1280, 720);
	return true;
}
void title::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}