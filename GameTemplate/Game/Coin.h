#pragma once

class Coin :public IGameObject
{
public:
	Coin();
	~Coin();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_coin = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale;
};

