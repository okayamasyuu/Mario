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
	m_enemy->Init(L"modelData/Angel.cmo");	//ゴールオブジェクト

	m_position.x = 300;
	scela = { 5,5,5 };

	m_enemy->SetPosition(m_position);
	m_enemy->SetScale(scela);
	return true;
}
void Enemy1::Update()
{

}
