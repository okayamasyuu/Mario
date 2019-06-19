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
	//XZ�����̈ړ����x���N���A
	m_moveSpeed.x = 0.0;
	m_moveSpeed.z = 0.0;

	m_moveSpeed += cameraForward * LSticky * 500.0f;
	m_moveSpeed += cameraRight * LStickx * 500.0f;


	//�d��
	//m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����

	m_skinModelRender->SetPosition(m_position);//�v���C���[�Ɉړ���������
	m_skinModelRender->SetRotation(m_rotation);
}
