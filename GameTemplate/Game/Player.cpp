#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(font);
}

bool Player::Start()
{
	//ワイヤーフレーム表示を有効にする
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	m_position.y = -250;
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,        //半径 大きさ
		80.0,       //高さ
		m_position
	);

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
	if (m_state == 1 && m_charaCon.IsJump()) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump,0.3);
		if (m_charaCon.IsOnGround()) {
			m_state = 0;
			m_skinModelRender->PlayAnimation(enAnimationClip_idle,0.3);
		}
	}
	else if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
			m_state = 1;
			m_moveSpeed.y = 500.0f;
	}
	//歩き歩き
	else if (m_moveSpeed.LengthSq() > 50 * 50) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run,0.3);
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
	
	

	
	cameraForward.y = 0.0;
	cameraForward.Normalize();
	cameraRight.y = 0.0;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア
	m_moveSpeed.x = 0.0;
	m_moveSpeed.z = 0.0;

	m_moveSpeed += cameraForward * LSticky * 500.0f;
	m_moveSpeed += cameraRight * LStickx * 500.0f;


	//重力
	m_moveSpeed.y -= 900.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える

	//m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える

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
	swprintf(text, L"HP%02d", HP);

	font->SetText(text);
	font->SetPosition({ -320, 300 });
}
void Player::blink()
{
	//点滅処理
	if (muteki == true) {
		int Inbizible = 2;

		if ((mutekitime / Inbizible) % 2 == 0) {
			m_skinModelRender->SetActiveFlag(false);
		}
		else {
			m_skinModelRender->SetActiveFlag(true);
		}

		if (mutekitime >= 100) {
			m_skinModelRender->SetActiveFlag(true);
			muteki = false;
			mutekitime = 0;
		}
	}
}