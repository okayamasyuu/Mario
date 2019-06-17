#pragma once

class Enemy1 : public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_enemy = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scela;
};
