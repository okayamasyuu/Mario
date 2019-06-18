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
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,        //���a �傫��
		100.0,       //����
		m_position
	);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	return true;
}
void Player::Update()
{
	camera = FindGO<Camera>("�J����");

	//CVector3 cameraForward = camera->GetCameraTargetPos() - camera->GetcamePos();
	//cameraForward.y = 0.0f;
	//cameraForward.Normalize();
	//m_position += cameraForward * 5.0f * pad.GetLStickYF();

	//CVector3 cameraRight;
	//cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	//cameraRight.Normalize();
	//m_position += cameraRight * 5.0f * pad.GetLStickXF();
	

	m_moveSpeed.x = pad.GetLStickXF() * 750.0f;
	m_moveSpeed.z = pad.GetLStickYF() * 750.0f;

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

	//�d��
	m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����

	m_skinModelRender->SetPosition(m_position);//�v���C���[�Ɉړ���������
}
