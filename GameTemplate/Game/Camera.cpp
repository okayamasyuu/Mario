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
	if (GetAsyncKeyState(VK_LEFT)) { 
		mRotY.MakeRotationY(CMath::DegToRad(100.0));//回転する値
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		mRotY.MakeRotationY(CMath::DegToRad(-10.0));
	}
	//ベクトルと行列を乗算して回転させる
	mRotY.Mul(toCameraPos);

	//新しい視点を計算する
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //注視点
	MainCamera().SetPosition(camePos); //視点
	//MainCamera().SetViewAngle();//画角
	MainCamera().Update();

}
