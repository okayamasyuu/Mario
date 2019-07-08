#pragma once
class Player;
class Block : public IGameObject
{
public:
	Block();
	~Block();
	bool Start();
	void Update();
	void SetScale(CVector3 sca)
	{
		scale = sca;
	}

	void SetPosi(CVector3 posi)
	{
		m_position = posi;
	}
	//CMatrix GetWorldMatrix()
	//{
	//	//m_blockがワールド行列を保持しているので、それを返す。
	//	return  GetWorldMatrix();
	//}
	
private:
	prefab::CSkinModelRender* m_block = nullptr;
	CPhysicsStaticObject  m_PSObject;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 scale;
	
	int timer = 0;
	Player* m_pl = nullptr;
};

