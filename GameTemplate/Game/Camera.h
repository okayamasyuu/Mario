#pragma once
//#include <Player.h>
#include "tkEngine/camera/tkSpringCamera.h"
class Player;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	CVector3 GetCameraTargetPos()
	{
		return target;
	}
	CVector3 GetcamePos()
	{
		return camePos;
	}
private:
	//CVector3 m_position = CVector3::Zero; //座標
	CSpringCamera m_springCamera;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 target;
	CVector3 camePos;//座標
	CVector3 toCameraPos;
	Player* m_player = nullptr;
	//クラスの継承
	//ポイント型
};

