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
	m_enemy2animClip[enEnemy2AnimClip_walk].Load(L"animData/WorkEnemymotion.tka");

	m_enemy2animClip[enEnemy2AnimClip_walk].SetLoopFlag(true);


	m_enemy2 = NewGO<prefab::CSkinModelRender>(0);
	m_enemy2->Init(L"modelData/WorkEnemy.cmo", m_enemy2animClip, enEnemy2AnimClip_Num);
	
	CVector3 scale = { 3,3,3 };

	m_position.x = -100;
	m_position.y = -50;

	m_enemy2->SetPosition(m_position);
	m_enemy2->SetScale(scale);
	m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
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
