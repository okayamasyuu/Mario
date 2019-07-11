#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy3::Enemy3()
{
}


Enemy3::~Enemy3()
{
	DeleteGO(m_enemy3);
}
bool Enemy3::Start()
{
	//m_enemy3animClip[enEnemyAnimClip_sky].Load(L"animData/WorkEnemymotion.tka");

	//m_enemy3animClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_enemy3 = NewGO<prefab::CSkinModelRender>(0);
	//m_enemy3->Init(L"modelData/Angel.cmo", m_enemy3animClip, enEnemyAnimClip_Num);

	m_enemy3->Init(L"modelData/Angel.cmo");


	m_EnemyCharaCon.Init(
		10.0,        //半径
		10.0,       //高さ
		m_position
	);

	for (int i = 0; i < 1; i++) {

		//ボックス形状のゴースト作成する
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //第一引数は座標。
			CQuaternion::Identity,     //第二引数は回転クォータニオン。
			{ 12.0, 5.0, 12.0 }     //第三引数はボックスのサイズ。
		);
	}

	m_moveSpeed.y = 150;
	m_enemy3->SetShadowCasterFlag(true);

	m_enemy3->SetPosition(m_position);
	m_enemy3->SetScale(scena);
	m_enemy3->SetRotation(m_rot);
	//m_enemy3->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy3::Update()
{
	m_pl = FindGO<Player>("プレイヤー");
	m_goalflaag = FindGO<GoalFlaag>("ゴールオブジェクト");

	m_position += m_moveSpeed;

	//上下に移動
	timer++;
	
	if (timer >= 20 ){
		timer = 0;
	    m_moveSpeed.y *= -1.0;//↓
	}
	if (timer >= 20 && m_moveSpeed.y < 0) {
		m_moveSpeed.y *= 1.0;//↑
	}

	GhostObj();

	//キャラコンに移動速度を与える
	m_position = m_EnemyCharaCon.Execute(m_moveSpeed);

	//ゴーストをエネミーと一緒に移動させる
	CVector3 pos = m_position;
	pos.y += 30;
	m_ghostobj.SetPosition(pos);

	////キャラコンで動かした結果をCSkinModelRenderに反映させる。
	m_enemy3->SetPosition(m_EnemyCharaCon.GetPosition());

}
void Enemy3::GhostObj()
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