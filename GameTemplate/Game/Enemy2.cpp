#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy2::Enemy2()
{
}


Enemy2::~Enemy2()
{
	DeleteGO(m_enemy2);
}
bool Enemy2::Start()
{
	m_enemy2 = NewGO<prefab::CSkinModelRender>(0);
	//m_enemy2->Init(L"");
	CVector3 scale = { 2,2,2 };

	m_position.x = -300;
	m_position.y = 100;

	m_enemy2->SetPosition(m_position);
	m_enemy2->SetScale(scale);
	return true;
}
void Enemy2::Update()
{
	m_pl = FindGO<Player>("プレイヤー");
	m_goalflaag = FindGO<GoalFlaag>("ゴールオブジェクト");

	//クリボーのシステム

	m_position += m_moveSpeed;


	//HPダメージ



}
void Enemy2::Turn()
{

}
