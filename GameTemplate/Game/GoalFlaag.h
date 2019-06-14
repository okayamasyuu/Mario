#pragma once
class Game;
class GoalFlaag : public IGameObject
{
public:
	GoalFlaag();
	~GoalFlaag();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_goalflaagModel = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scela;
	Game* ga = nullptr;
};

