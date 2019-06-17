#pragma once
#include "Game.h"
class Game;
class GoalFlaag : public IGameObject
{
public:
	GoalFlaag();
	~GoalFlaag();
	bool Start();
	void Update();
	void SetClear_flag(bool flag)
	{
		Clear_flag = flag;
	}
	bool GetClearFlag() 
	{
		return Clear_flag;
	}
private:
	prefab::CSkinModelRender* m_goalflaagModel = nullptr;
	CPhysicsStaticObject m_PSOject;
	CVector3 m_position = CVector3::Zero;
	CVector3 scela;
	bool Clear_flag = false; //クリアフラグ
	Game* ga = nullptr;
};

