#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
//#include "Game.h"
#include "Score.h"

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

	//scale = { 3,3,3 };
	//m_position = { 100,-140,0 };
	m_coin->SetShadowCasterFlag(true);

	m_coin->SetEmissionColor({ 0.3, 0.3, 0 });

	m_coin->SetPosition(m_position);
	m_coin->SetScale(scale);
	return true;
}
void Coin::Update()
{
	m_score = FindGO<Score>("スコア");

	//回転
	CQuaternion Rot;
	Rot.SetRotationDeg(
		{ 0.0f, 1.0, 0.0 },
		3.0f);
	m_rotation *= Rot;

	//コインとプレイヤーとの当たり判定
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		if (diff.Length() < 28) {
			//効果音
			auto ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/coinGet.wav");
			ss->SetVolume(11.0f);
			ss->Play(false);

			//スコアに加算する
			m_score->TasuScore(10);

			DeleteGO(this);
		}
		return true;
	});
	m_coin->SetRotation(m_rotation);
}
