#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start()
{
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,        //半径 大きさ
		100.0,       //高さ
		m_position
	);

	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	
	//ループフラグを設定する。<-走りアニメーションはループフラグを設定していないので
	//ワンショット再生で停止する。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	jump = NewGO<prefab::CSoundSource>(0);
	jump->Init(L"sound/jump.wav");
	jump->SetVolume(10.0f);
	return true;
}
void Player::Update()
{
	//camera = FindGO<Camera>("カメラ");

	
	
	float LStickx = pad.GetLStickXF();
	float LSticky = pad.GetLStickYF();

	if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
		jump->Play(false);
		m_moveSpeed.y = 300.0f;
		DeleteGO(jump);
	}
	else if(m_charaCon.IsOnGround() && Pad(0).IsPress(enButtonB)){
		m_moveSpeed.x = LStickx * 850.0;
		m_moveSpeed.z = LSticky * 850.0;
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
    }
	else {
		m_animClips[enAnimationClip_run].SetLoopFlag(false);
		m_skinModelRender->PlayAnimation(enAnimationClip_idle); //た
	}

	

	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();

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
	m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える

	//m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える

	Turn();

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