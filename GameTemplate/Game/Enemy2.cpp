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
	
	CVector3 scale = { 4,4,4 };

	m_position.x = -400;
	m_position.y = -200;

	//キャラコンの初期化
	m_Enemy2CharaCon.Init(
		25.0,        //半径
		47.0,       //高さ
		m_position
	);
	
	for (int i = 0; i < 1; i++) {

		//ボックス形状のゴースト作成する
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //第一引数は座標。
			CQuaternion::Identity,     //第二引数は回転クォータニオン。
			{ 30.0, 5.0, 30.0 }     //第三引数はボックスのサイズ。
		);
	}
	
	m_enemy2->SetPosition(m_position);
	m_enemy2->SetScale(scale);
	//m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
	return true;
}
void Enemy2::Update()
{
	m_pl = FindGO<Player>("プレイヤー");
	m_goalflaag = FindGO<GoalFlaag>("ゴールオブジェクト");

	//ゲームのクラスのポインタを返す
	//m_pl = Game::GetInstance()->m_pl;
	//m_goalflaag = Game::GetInstance()->m_goaflaag;

	//クリボーのシステム

	m_position += m_moveSpeed;

	//プレイヤーを追いかける
	CVector3 toPlayer = { 0,0,0 };
	toPlayer = m_pl->GetPosi() - m_position;

	//toPlayerの距離を計算
	float len = toPlayer.Length();

	///////視野角
	CVector3 enemyForward = CVector3::AxisZ;
	m_rot.Multiply(enemyForward);

	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_pl->GetPosi() - m_position;
	//正規化を行う前に、プレイヤーまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化！
	toPlayerDir.Normalize();
	//enemyForwardとtoPlayerDirとの内積を計算する。
	float d = enemyForward.Dot(toPlayerDir);
	//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);
	//視野角判定
	//fabsfは絶対値を求める関数！
	//角度はマイナスが存在するから、絶対値にする。
	if (fabsf(angle) < CMath::DegToRad(90.0f)
		&& toPlayerLen < 500.0f){
		toPlayer.Normalize();
		//スピード
		toPlayer.x *= 10;
		toPlayer.z *= 10;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		//if (m_moveSpeed.LengthSq() > 10 * 10) {
			m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
		//}
	}
	//範囲
	//if (len < 500) {
	//	toPlayer.Normalize();
	//	//スピード
	//	toPlayer.x *= 10;
	//	toPlayer.z *= 10;
	//	m_moveSpeed.x += toPlayer.x;
	//	m_moveSpeed.z += toPlayer.z;
	//	if (m_moveSpeed.LengthSq() > 10 * 10) {
	//		m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
	//	}
	//}
	else {
		toPlayer.x *= 0;
		toPlayer.z *= 0;
		m_moveSpeed.x = toPlayer.x;
		m_moveSpeed.z = toPlayer.z;
	}

	//HPダメージ
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		//無敵時間
		/*if (pl->GetMutekiFlag() == true) {
			pl->TasuMutekiTime(1);
			if (pl->GetMutekiTime() == 100) {
				pl->SetMutekiFlag(false);
				pl->SetMutekiTime(0);
			}
		}*/

		//距離小さくなったら
		//距離0.5前後ぐらい
		if (diff.Length() < 0.8 && m_goalflaag->GetClearFlag() == false
			&& pl->GetHP() > 0 && pl->GetMutekiFlag() == false) {
			//HPダメージ
			pl->HikuHP(1);
			//無敵
			pl->SetMutekiFlag(true);
		}
		return true;
	});

	GhostObj();

	//重力
	m_moveSpeed.y -= 700.0 * GameTime().GetFrameDeltaTime();

	//キャラコンに移動速度を与える
	m_position = m_Enemy2CharaCon.Execute(m_moveSpeed);
	
	//ゴーストをエネミーと一緒に移動させる
	CVector3 pos = m_position;	
	pos.y += 120;
	m_ghostobj.SetPosition(pos);

	//キャラコンで動かした結果をCSkinModelRenderに反映させる。
	m_enemy2->SetPosition(m_Enemy2CharaCon.GetPosition());

	Turn();

	m_enemy2->SetRotation(m_rot);
}
void Enemy2::Turn()
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
void Enemy2::GhostObj()
{
	//ゴーストオブジェクトの当たり判定(プレイヤー)
	PhysicsWorld().ContactTest(m_pl->m_charaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {
			//踏んだら飛ぶ
			m_pl->SetMoveSpeed({ 0,300,0 });
			DeleteGO(this); //当たったら破棄
		}
	});
}