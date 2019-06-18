#include "stdafx.h"
#include "title.h"
#include "Game.h"

title::title()
{
}


title::~title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(soundRender);
}
bool title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Mario.Title.dds", 1280.0f, 720.0f);
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/taitle1.wav");
	APress = NewGO<prefab::CSoundSource>(0);
	APress->Init(L"sound/nanndeyanen.wav");
	return true;
}
void title::Update()
{
	soundRender->Play(true);
	if (Pad(0).IsTrigger(enButtonA)) {
		soundRender->Stop();
		APress->Play(false);
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}