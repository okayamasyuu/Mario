#pragma once
#include <Camera.h>
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
	}
	CVector3 GetPosi()
	{
		return m_position;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CCharacterController m_charaCon; //キャラクターコントローラー
	
};

