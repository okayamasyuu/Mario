#pragma once
class Score;
class Coin :public IGameObject
{
public:
	Coin();
	~Coin();
	bool Start();
	void Update();
	void SetScale(CVector3 sca)
	{
		scale = sca;
	}
	void SetPosi(CVector3 pos)
	{
		m_position = pos;
	}

private:
	Score* m_score = nullptr;
	prefab::CSkinModelRender* m_coin = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 scale;
	
};

