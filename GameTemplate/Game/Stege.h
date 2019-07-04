#pragma once
class Stege : public IGameObject
{
public:
	Stege();
	~Stege();
	bool Start();
	void SetPosi(CVector3 posi)
	{
		m_position = posi;
	}
	
private:
	prefab::CSkinModelRender* m_StegeModelRender = nullptr;
	CPhysicsStaticObject m_PSOject;
	CVector3 m_position = CVector3::Zero;
	CVector3 scela;

};

