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

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
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
	//camera = FindGO<Camera>("�J����");

	
	
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
		m_skinModelRender->PlayAnimation(enAnimationClip_idle); //��
	}

	

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
	m_moveSpeed.y -= 500.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����

	//m_skinModelRender->SetPosition(m_position);//�v���C���[�Ɉړ���������

	Turn();

	//3dMax��Ő����̐ݒ肳��Ă���̂ŉ�]����
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	qRot.Multiply(m_rotation, qRot);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
}
void Player::Turn()
{
	//Player�̉�]
	if (fabsf(m_moveSpeed.x) < 0.001f && 
		fabsf(m_moveSpeed.z) < 0.001f ){
		return;
	}
	//�p�x�����߂Ă���
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	//Z����]
	m_rotation.SetRotation(CVector3::AxisZ, -angle);
}