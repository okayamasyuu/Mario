#include "stdafx.h"
#include "Player.h"
#include "Block.h"
#include "Game.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "GoalFlaag.h"

Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(font);
	DeleteGO(HPmae);
	DeleteGO(HPusiro);
}

bool Player::Start()
{
	//ワイヤーフレーム表示を有効にする
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	//m_position.y = -250;
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		10.0,        //半径 大きさ
		20.0,       //高さ
		m_position
	);
	
	//for (int i = 0; i < 1; i++) {

	//	//ボックス形状のゴースト作成する
	//	m_ghostobj.CreateBox(
	//		ghostPosi = m_position,    //第一引数は座標。
	//		CQuaternion::Identity,     //第二引数は回転クォータニオン。
	//		{ 12.0, 4.0, 12.0 }     //第三引数はボックスのサイズ。
	//	);
	//}
	//HPUI
	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Black);


	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClips[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClips[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	
	//ループフラグを設定する。<-走りアニメーションはループフラグを設定していないので
	//ワンショット再生で停止する。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->PlayAnimation(enAnimationClip_idle);

	HPmae = NewGO<prefab::CSpriteRender>(0);
	HPmae->Init(L"sprite/HPmae.dds", 150.0f, 100.0f);
	HPmae->SetPosition(HPmaePos);
	HPusiro = NewGO<prefab::CSpriteRender>(0);
	HPusiro->Init(L"sprite/HPusiro.dds", 200.0f, 100.0f);
	HPusiro->SetPosition(HPusiroPos);
	m_skinModelRender->SetShadowCasterFlag(true);

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	return true;
}
void Player::Update()
{
	//camera = FindGO<Camera>("カメラ");

	blink();

	float LStickx = pad.GetLStickXF();
	float LSticky = pad.GetLStickYF();
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();


	//ジャンプ
	if (m_charaCon.IsJump()) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump, 0.3);
		//if (m_charaCon.IsOnGround()) {
		m_state = 0;
		//m_skinModelRender->PlayAnimation(enAnimationClip_idle,0.3);
	//}
	}
	else if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
		m_state = 1;
		m_moveSpeed.y = 350.0f;
	}
	//歩き歩き
	else if (m_moveSpeed.LengthSq() > 30 * 30) {
		
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.3);
	}
	/*else if (m_moveSpeed.LengthSq() > 600 * 600 && m_state == 2) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.3);
	}*/
	////ダッシュ
	//else if(m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonB)){
	//	m_state = 2;
	//	m_moveSpeed += cameraForward * LSticky * 800.0f;
	//	m_moveSpeed += cameraRight * LStickx * 800.0f;
	//
	//	/*m_skinModelRender->PlayAnimation( enAnimationClip_run,0.3);*/
 //   }
	//待機
	else {
		m_state = 5;
		m_skinModelRender->PlayAnimation(enAnimationClip_idle); //た
	}


	EnemyColider();

	//GhostObj();

	cameraForward.y = 0.0;
	cameraForward.Normalize();
	cameraRight.y = 0.0;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア
	m_moveSpeed.x = 0.0;
	m_moveSpeed.z = 0.0;

	m_moveSpeed += cameraForward * LSticky * 200.0f;
	m_moveSpeed += cameraRight * LStickx * 200.0f;

	
	////加速度の計算
	//CVector3 accForwardXZ = MainCamera().GetForward();
	//CVector3 accRightXZ = MainCamera().GetRight();
	//accForwardXZ.y = 0.0f;
	//accForwardXZ.Normalize();
	//accRightXZ.y = 0.0f;
	//accRightXZ.Normalize();

	////摩擦力。
	//CVector3 friction = m_moveSpeed;
	//if (m_charaCon.IsJump()) {
	//	//ジャンプ中の摩擦力。
	//	friction *= -1.0f;
	//}
	//else {
	//	friction *= -3.0f;
	//}
	//m_moveSpeed.x += friction.x * GameTime().GetFrameDeltaTime();
	//m_moveSpeed.z += friction.z * GameTime().GetFrameDeltaTime();

	////加速度を加える。
	//m_moveSpeed += accForwardXZ;
	//m_moveSpeed += accRightXZ;

	////重力
	//m_moveSpeed.y -= 900.0 * GameTime().GetFrameDeltaTime();
	//if (m_charaCon.IsJump()) {
	//	//移動速度に制限を加える。
	//	//ジャンプ中にジャンプ前より早くなることはない
	//	CVector3 moveSpeedXZ = CVector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

	//	if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
	//		moveSpeedXZ.Normalize();
	//		moveSpeedXZ *= m_moveSpeedWhenStartJump;
	//		m_moveSpeed.x = moveSpeedXZ.x;
	//		m_moveSpeed.z = moveSpeedXZ.z;
	//	}
	//}

	////普通にワールド行列を作ると・・・
	//CMatrix mWorld;
	//mWorld.MakeTranslation(m_position);
	////床のワールド行列を乗算して、子供に影響を与えてみる
	//mWorld.Mul(mWorld, parent->GetWorldMatrix());
	////行列をモデルに設定する
	//m_skinModelRender->(mWorld);

	//重力
	m_moveSpeed.y -= 900.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える

	//ゴーストをエネミーと一緒に移動させる
	/*CVector3 pos = m_position;
	pos.y += 30;
	m_ghostobj.SetPosition(pos);*/

	m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える

	Turn();

	HPUI();

	

	//3dMax上で成分の設定されているので回転する
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	qRot.Multiply(m_rotation, qRot);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
}
void Player::Turn()
{
	//Playerの回転
	if (fabsf(m_moveSpeed.x) < 0.001f && 
		fabsf(m_moveSpeed.z) < 0.001f ){
		return;
	}
	//角度を求めている
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	//Z軸回転
	m_rotation.SetRotation(CVector3::AxisZ, -angle);
}
void Player::HPUI()
{
	//HP
	wchar_t text[256];
	swprintf(text, L"%02d / 10", HP);

	font->SetText(text);
	font->SetPosition({ 400, 250 });

	if (HP <= 5) {
		font->SetColor(color);
	}
}
void Player::blink()
{
	//点滅処理
	if (muteki == true) {
		mutekitime++;
		const int Inbizible = 3;

		if ((mutekitime / Inbizible) % 2 == 0) {
			m_skinModelRender->SetActiveFlag(false);
		}
		else {
			m_skinModelRender->SetActiveFlag(true);
		}

		if (mutekitime >= 100 ) {
			m_skinModelRender->SetActiveFlag(true);
			muteki = false;
			mutekitime = 0;
		}
	}
}
void Player::Coinget()
{
	//コインができたらここに書く
	//例文
	/*
	if(コインとプレイヤーの距離 <= 50){
	count++;
	DeleteGO(当たったコイン);
	}
	*/
}
void Player::EnemyColider()
{
	QueryGOs<Enemy2>("敵2", [&](Enemy2 * en2)->bool {
		CVector3 diff2 = m_position - en2->GetPosi();
		m_goal = Game::GetInstance()->m_goal;
		//距離25前後ぐらい
		if (diff2.Length() < 25 && m_goal->GetClearFlag() == false
			&& HP > 0 && muteki == false) {
			//HPダメージ
			HP--;
			//pl->HPmae.x - Tidimaru.x;
			//無敵
			muteki = true;
		}
		return true;
	});
	//HPダメージ
	QueryGOs<Enemy1>("敵1", [&](Enemy1 * en1)->bool {
	
			m_goal = Game::GetInstance()->m_goal;
			CVector3 diff1 = m_position - en1->GetPosi();
			
			//距離小さくなったら
			//距離25前後ぐらい
			if (diff1.Length() < 28 && m_goal->GetClearFlag() == false
				&& HP > 0 && muteki == false) {
				//HPダメージ
				HP--;
				//pl->HPmae.x - Tidimaru.x;
				//無敵
				muteki = true;
			}
			
		return true;
	});
}
void Player::GhostObj()
{
	m_en1 = Game::GetInstance()->m_en1;
	//ゴーストオブジェクトの当たり判定(敵1)
	PhysicsWorld().ContactTest(m_en1->m_EnemyCharaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject) && muteki == false) {
			//踏んだら飛ぶ
			HP--;
			muteki = true;
			m_en1->SetMoveSpeed({ 0,200,0 });
			//DeleteGO(this); //当たったら破棄
		}
		else if (m_ghostobj.IsSelf(contactObject) && muteki == true) {
			m_en1->SetMoveSpeed({ 0,200,0 });
		}
	});
}