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
	

	//���_�v�Z
	//CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	//camePos = target + Pos; //�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���
	//camePos = target;

	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	toCameraPos.Set(0.0, 100, 500);

	//���_�̏ꏊ
	//camePos.y += 400.0f;
	//camePos.z -= 500.0f;
	return true;
}
void Camera::Update()
{
	//�N���X�p�������ă|�C���g�^�ɂ��ăC���X�^���X��T���i���O�j
	m_player = FindGO<Player>("�v���C���[");
	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = m_player->GetPosi();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;

	CVector3 toCameraPosOld = toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toCameraPos);
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.7f) {
		//�J����������������B
		toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		toCameraPos = toCameraPosOld;
	}

	//�V�������_���v�Z����
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //�����_
	MainCamera().SetPosition(camePos); //���_
	//MainCamera().SetViewAngle();//��p
	MainCamera().Update();

}
