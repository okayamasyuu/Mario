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
	//�J�����̉�]
	//���_�̐ݒ��Update�ł͂Ȃ�Start()�ŌĂяo��
	//�o�Ȃ���Γ��͂��������ŉ�]�����㌳�̈ʒu�ɖ߂��Ă��܂�

	//���_�v�Z
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	camePos = target + Pos; //�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���
	camePos = target;

	//���_�̏ꏊ
	camePos.y += 400.0f;
	camePos.z -= 800.0f;
	return true;
}
void Camera::Update()
{
	//�N���X�p�������ă|�C���g�^�ɂ��ăC���X�^���X��T���i���O�j
	m_player = FindGO<Player>("�v���C���[");

	

	target = m_player->GetPosi(); //�����_

	target.y += 50.0f;
	//�����_���王�_�Ɍ������ĐL�т�x�N�g��
	CVector3 toCameraPos = camePos - target;
	CVector3 toCameraPosOld = toCameraPos;

	//float x = m_player->pad.GetRStickXF();
	//float y = m_player->pad.GetRStickYF();
	//����]
	//CQuaternion qRot;
	//qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	//qRot.Apply(toCameraPos);
	//
	////�c��]
	//CVector3 axisX;
	//axisX.Cross(CVector3::AxisX, toCameraPos);
	//axisX.Normalize();
	//qRot.SetRotationDeg(axisX, 2.0 * y);
	//qRot.Apply(toCameraPos);
	//CVector3 toPosDir = toCameraPos;
	//toPosDir.Normalize();
	
	//��]�s��
	CMatrix mRotY;
	mRotY = CMatrix::Identity;

	//�E�X�e�B�b�N
		mRotY.MakeRotationY(CMath::DegToRad(2.0f) * m_player->pad.GetRStickXF());
		mRotY.Mul(toCameraPos);
	
	//�܂��A�񂷎����v�Z����B
	CVector3 rotAxis;
	CVector3 upAxis(0.0f, 1.0f, 0.0f);
	rotAxis.Cross(upAxis, toCameraPos);
	rotAxis.Normalize();
	mRotY = CMatrix::Identity;
	mRotY.MakeRotationAxis(rotAxis, CMath::DegToRad(2.0f) * m_player->pad.GetRStickYF());
	//�x�N�g���ƍs�����Z���ĉ�]������
	mRotY.Mul(toCameraPos);
	
	//�V�������_���v�Z����
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //�����_
	MainCamera().SetPosition(camePos); //���_
	//MainCamera().SetViewAngle();//��p
	MainCamera().Update();

}
