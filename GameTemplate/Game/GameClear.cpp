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
	m_gameClearSprite = NewGO<prefab::CSpriteRender>(0);
	m_gameClearSprite->Init(L"sprite/GAMECLEAR.dds",500,300);
	return true;
}
void GameClear::Update()
{

}