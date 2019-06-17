#pragma once
//#include <Player.h>
class Player;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	
private:
	CVector3 m_position = CVector3::Zero; //座標
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 target;
	CVector3 camePos;
	Player* m_player = nullptr;
	//クラスの継承
	//ポイント型
};

