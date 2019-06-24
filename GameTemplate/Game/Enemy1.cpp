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
	//m_enemy->Init(L"modelData/Angel.cmo", m_enemyanimClip,enEnemyAnimClip_Num);
	m_enemy->Init(L"modelData/Angel.cmo");
	CVector3 scena = {
		4,
		4,
		4,

	};

	//m_enemyanimClip[enEnemyAnimClip_sky].Load(L"animData/angelmotion.tka");

	//m_enemyanimClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_position.y = 150;
	m_enemy->SetPosition(m_position);
	m_enemy->SetScale(scena);
	//m_enemy->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy1::Update()
{
	//QueryGO()
}