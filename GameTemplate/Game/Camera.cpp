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
	

	//視点計算
	//CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	//camePos = target + Pos; //キャラクタを斜め上から見ているような視点にする
	//camePos = target;

	//注視点から視点までのベクトルを設定。
	toCameraPos.Set(0.0, 100, 500);

	//視点の場所
	//camePos.y += 400.0f;
	//camePos.z -= 500.0f;
	return true;
}
void Camera::Update()
{
	//クラス継承をしてポイント型にしてインスタンスを探す（名前）
	m_player = FindGO<Player>("プレイヤー");
	//カメラを更新。
	//注視点を計算する。
	CVector3 target = m_player->GetPosi();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 50.0f;

	CVector3 toCameraPosOld = toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	qRot.Multiply(toCameraPos);
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.7f) {
		//カメラが上向きすぎ。
		toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		toCameraPos = toCameraPosOld;
	}

	//新しい視点を計算する
	camePos = target + toCameraPos;

	MainCamera().SetTarget(target);  //注視点
	MainCamera().SetPosition(camePos); //視点
	//MainCamera().SetViewAngle();//画角
	MainCamera().Update();

}
