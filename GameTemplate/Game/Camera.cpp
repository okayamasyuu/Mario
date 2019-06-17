#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}
bool Camera::Start()
{

	return true;
}
void Camera::Update()
{
	//�N���X�p�������ă|�C���g�^�ɂ��ăC���X�^���X��T���i���O�j
	m_player = FindGO<Player>("�v���C���[");

	target = m_player->GetPosi(); //�����_

	target.y += 50.0f;

	//���_�v�Z
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
    camePos = target + Pos; //�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���
	camePos = target;

	//���_�̏ꏊ
	camePos.y += 400.0f;
	camePos.z -= 800.0f;


	//�����_���王�_�Ɍ������ĐL�т�x�N�g��
	CVector3 toCameraPos = camePos - target;

	CMatrix mRot;
	mRot = CMatrix::Identity;
	if (GetAsyncKeyState(VK_LEFT)) {
		mRot.MakeRotationY(CMath::DegToRad(1.0f));
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		mRot.MakeRotationY(CMath::DegToRad(-1.0f));
	}
	mRot.Mul(toCameraPos);

	

	////�V�������_���v�Z����
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //�����_
	MainCamera().SetPosition(camePos); //���_
	//MainCamera().SetViewAngle();//��p
	MainCamera().Update();

}
