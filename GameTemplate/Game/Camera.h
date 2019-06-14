#pragma once
#include <Player.h>
class Player;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	
private:
	CVector3 m_position = CVector3::Zero; //ç¿ïW
	CVector3 target;
	CVector3 camePos;
	Player* m_player = nullptr;
};

