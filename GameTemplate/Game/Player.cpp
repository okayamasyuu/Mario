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
	//���C���[�t���[���\����L���ɂ���
	PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,        //���a �傫��
		100.0,       //����
		m_position
	);

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClips[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClips[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
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
	//camera = FindGO<Camera>("�J����");



	float LStickx = pad.GetLStickXF();
	float LSticky = pad.GetLStickYF();

	
	//�W�����v
	if (m_state = 1 && m_charaCon.IsJump()) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump,0.3);
		if (m_charaCon.IsOnGround()) {
			m_state = 0;
			m_skinModelRender->PlayAnimation(enAnimationClip_idle,0.3);
		}
	}
	if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
			m_state = 1;
			m_moveSpeed.y = 300.0f;
	}
	//����
	if (m_moveSpeed.LengthSq() > 50 * 50) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk,0.3);
	}
	//�_�b�V��
	else if(m_charaCon.IsOnGround() && Pad(0).IsPress(enButtonB) && m_moveSpeed.LengthSq() > 600 * 600){
		m_moveSpeed.x = pad.GetLStickXF() * 850.0;
		m_moveSpeed.z = pad.GetLStickYF() * 850.0;
	
		m_skinModelRender->PlayAnimation( enAnimationClip_run,0.3);
    }
	//�ҋ@
	else {
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