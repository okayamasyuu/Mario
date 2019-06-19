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

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	return true;
}
void Player::Update()
{
	camera = FindGO<Camera>("カメラ");

	//m_moveSpeed.x = pad.GetLStickXF() * 750.0f;
	//m_moveSpeed.z = pad.GetLStickYF() * 750.0f;

	/*if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
		m_moveSpeed.y = 300.0f;
	}
	if(m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonB)){
		m_moveSpeed.x = pad.GetLStickXF() * 850.0;
		m_moveSpeed.y = pad.GetLStickYF() * 850.0;
    }*/

	float LStickx = pad.GetLStickXF();
	float LSticky = pad.GetLStickYF();

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
	//m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える

	m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える
	m_skinModelRender->SetRotation(m_rotation);
}
