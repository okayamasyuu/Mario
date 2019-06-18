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
	//クラス継承をしてポイント型にしてインスタンスを探す（名前）
	m_player = FindGO<Player>("プレイヤー");

	

	target = m_player->GetPosi(); //注視点

	target.y += 50.0f;

	//視点計算
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
    camePos = target + Pos; //キャラクタを斜め上から見ているような視点にする
	camePos = target;

	//視点の場所
	camePos.y += 400.0f;
	camePos.z -= 800.0f;

	//注視点から視点に向かって伸びるベクトル
	CVector3 toCameraPos = camePos - target;
	//回転行列
	CMatrix mRotY;
	mRotY = CMatrix::Identity;

	//右スティック
		mRotY.MakeRotationY(CMath::DegToRad(50.0f) * m_player->pad.GetRStickXF());
		mRotY.Mul(toCameraPos);
	
	//まず、回す軸を計算する。
	CVector3 rotAxis;
	CVector3 upAxis(0.0f, 1.0f, 0.0f);
	rotAxis.Cross(upAxis, toCameraPos);
	rotAxis.Normalize();
	mRotY = CMatrix::Identity;
	mRotY.MakeRotationAxis(rotAxis, CMath::DegToRad(50.0f) * m_player->pad.GetRStickYF());
	//ベクトルと行列を乗算して回転させる
	mRotY.Mul(toCameraPos);
	
	//新しい視点を計算する
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //注視点
	MainCamera().SetPosition(camePos); //視点
	//MainCamera().SetViewAngle();//画角
	MainCamera().Update();0

}
