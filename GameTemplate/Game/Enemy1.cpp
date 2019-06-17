#include "stdafx.h"
#include "Enemy1.h"


Enemy1::Enemy1()
{
}


Enemy1::~Enemy1()
{
	DeleteGO(m_enemy);
}
bool Enemy1::Start()
{
	m_enemy = NewGO<prefab::CSkinModelRender>(0);
	m_enemy->Init(L"modelData/Angel.cmo");
	return true;
}
void Enemy1::Update()
{

}