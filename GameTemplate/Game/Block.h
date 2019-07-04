#pragma once
class Player;
class Block : public IGameObject
{
public:
	Block();
	~Block();
	bool Start();
	void Update();
	void SetPosi(CVector3 posi)
	{
		m_position = posi;
	}
private:
	prefab::CSkinModelRender* m_block = nullptr;
	CPhysicsStaticObject  m_PSObject;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale;
};

