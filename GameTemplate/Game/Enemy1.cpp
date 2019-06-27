#include "stdafx.h"
#include "Enemy1.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy1::Enemy1()
{
}


Enemy1::~Enemy1()
{
	DeleteGO(m_enemy);
}
bool Enemy1::Start()
{
	

	//敵（ノコノコ）の数（i）　
	//for (int i = 0; i < 1; i++) {

	//	//ボックス形状のゴースト作成する
	//	m_ghostobj.CreateBox(
	//		ghostPosi = m_position,    //第一引数は座標。
	//		CQuaternion::Identity,     //第二引数は回転クォータニオン。
	//		{ 50.0, 10.0, 50.0 }     //第三引数はボックスのサイズ。
	//	);
	//}

	m_enemyanimClip[enEnemyAnimClip_sky].Load(L"animData/angelmotion.tka");

	m_enemyanimClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_enemy = NewGO<prefab::CSkinModelRender>(0);
	m_enemy->Init(L"modelData/Angel.cmo", m_enemyanimClip,enEnemyAnimClip_Num);
	//m_enemy->Init(L"modelData/Angel.cmo");
	CVector3 scena = {
		4,
		4,
		4,

	};
	//敵1のポジション位置、配列
	m_position.y = -250;
	m_position.x = -150;
	m_position.z = 350;
	//キャラコンの初期化
	m_EnemyCharaCon.Init(
		25.0,        //半径
		43.0,       //高さ
		m_position
	);

	m_enemy->SetPosition(m_position);
	m_enemy->SetScale(scena);
	m_enemy->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy1::Update()
{
	m_pl = FindGO<Player>("プレイヤー");
	m_goalflaag = FindGO<GoalFlaag>("ゴールオブジェクト");

	m_position += m_moveSpeed;

	//プレイヤーを追いかける
	CVector3 toPlayer = { 0,0,0 };
	toPlayer = m_pl->GetPosi() - m_position;

	//toPlayerの距離を計算
	float len = toPlayer.Length();

	//範囲
	if (len < 300) {
		toPlayer.Normalize();
		//スピード
		toPlayer.x *= 10;
		toPlayer.z *= 10;
		toPlayer.y *= 10;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		m_moveSpeed.y += toPlayer.y;
	}
	else {
		m_moveSpeed = { 0,0,0 };
	}

	//HPダメージ
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		//無敵時間
		if (pl->GetMutekiFlag() == true) {
			pl->TasuMutekiTime(1);
			if (pl->GetMutekiTime() == 100) {
				pl->SetMutekiFlag(false);
				pl->SetMutekiTime(0);
			}
		}

		//距離小さくなったら
		//距離0.5前後ぐらい
		if (diff.Length() < 0.7 && m_goalflaag->GetClearFlag() == false
			&& pl->GetHP() > 0 && pl->GetMutekiFlag() == false) {
			//HPダメージ
			pl->HikuHP(1);
			//無敵
			pl->SetMutekiFlag(true);
		}
		return true;
	});

	//GhostObj();

	//キャラコンに移動速度を与える
	m_position = m_EnemyCharaCon.Execute(m_moveSpeed);

	//キャラコンで動かした結果をCSkinModelRenderに反映させる。
	m_enemy->SetPosition(m_EnemyCharaCon.GetPosition());

	Turn();

	m_enemy->SetRotation(m_rot);
}
void Enemy1::Turn()
{
	//Enemyの回転
	if (fabsf(m_moveSpeed.x) < 0.001f &&
		fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//角度を求めている
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	//Y軸回転
	m_rot.SetRotation(CVector3::AxisY, angle);
}
void Enemy1::GhostObj()
{
	//ゴーストをエネミーと一緒に移動させる
	CVector3 pos = m_position;
	pos.y = -180;
	m_ghostobj.SetPosition(pos);
	m_ghostobj.SetPosition(m_position);

	//ゴーストオブジェクトの当たり判定(プレイヤー)
	PhysicsWorld().ContactTest(m_pl->m_charaCon,[&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {

			DeleteGO(this); //当たったら破棄
		}
	});
	
}