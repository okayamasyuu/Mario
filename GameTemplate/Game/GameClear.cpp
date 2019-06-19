#include "stdafx.h"
#include "GameClear.h"


GameClear::GameClear()
{
}


GameClear::~GameClear()
{
	DeleteGO(m_gameClearSprite);
}
bool GameClear::Start()
{
	sound = NewGO<prefab::CSoundSource>(0);
	sound->Init(L"sound/waraigoe.wav");
	sound->SetVolume(30.0f);
	sound->Play(false);
	m_gameClearSprite = NewGO<prefab::CSpriteRender>(0);
	m_gameClearSprite->Init(L"sprite/GAMECLEAR.dds",500,300);
	return true;
}
void GameClear::Update()
{

}