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

	target.y += 50.0f;
	return true;
}
void Camera::Update()
{
	//m_player = FindGO<Player>("�v���C���[");
	//target = m_player->GetPosi(); //�����_
//	target.y += 50.0f;

	//���_�v�Z
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	/*CVector3*/ camePos = target + Pos; //�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���
	camePos = target;

	//���_�̏ꏊ
	camePos.y += 400.0f;
	camePos.z -= 800.0f;



	MainCamera().SetTarget(target);  //�����_
	MainCamera().SetPosition(camePos); //���_
	//MainCamera().SetViewAngle();//��p
	MainCamera().Update();

}