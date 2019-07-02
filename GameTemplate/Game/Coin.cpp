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
	

	m_coin->SetPosition(m_position);
	m_coin->SetScale(scale);
	return true;
}
void Coin::Update()
{
	//�R�C���ƃv���C���[�Ƃ̓����蔻��
	QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		if (diff.Length() < 50) {

			DeleteGO(this);
		}
		return true;
	});
}
