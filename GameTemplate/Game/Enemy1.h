#pragma once
class Enemy1 : public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_enemy = nullptr;
};

