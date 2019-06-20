#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}
bool GameOver::Start()
{
	himei = NewGO<prefab::CSoundSource>(0);
	himei->Init(L"sound/himei.wav");
	himei->SetVolume(0.1f);
	himei->Play(false);
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/mu.dds", 500, 400);
	return true;
}
