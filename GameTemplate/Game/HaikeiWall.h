#pragma once
class HaikeiWall : public IGameObject
{
public:
	HaikeiWall();
	~HaikeiWall();
	bool Start();
	void SetScale(CVector3 sca)
	{
		scela = sca;
	}
	void SetPosi(CVector3 posi)
	{
		m_position = posi;
	}

private:
	prefab::CSkinModelRender* m_WallModelRender = nullptr;

	CVector3 m_position = CVector3::Zero;
	CVector3 scela;
};

