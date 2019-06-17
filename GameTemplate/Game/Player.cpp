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
	CPad& pad = Pad(0);
	m_moveSpeed.x = pad.GetLStickXF() * 750.0f;
	m_moveSpeed.z = pad.GetLStickYF() * 750.0f;

	camera = FindGO<Camera>("カメラ");

	/*CVector3 cameraDir = 
		camera->GetCameraTargetPos() - camera->GetcamePos();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	CVector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		{ 0,1,0 }
	);
	if (GetAsyncKeyState('F')) {
		m_position += cameraDirX * 3;
	}*/

	//重力
	m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える

	m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える
}
