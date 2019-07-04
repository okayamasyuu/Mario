#include "stdafx.h"
#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
}


Coin::~Coin()
{
	DeleteGO(m_coin);
}
bool Coin::Start()
{
	m_coin = NewGO<prefab::CSkinModelRender>(0);
	m_coin->Init(L"modelData/koin.cmo");

	scale = { 3,3,3 };
	m_position = { 100,-140,0 };
	m_coin->SetPosition(m_position);
	m_coin->SetScale(scale);
	return true;
}
void Coin::Update()
{
	//コインとプレイヤーとの当たり判定
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		if (diff.Length() < 50) {

			DeleteGO(this);
		}
		return true;
	});
}
