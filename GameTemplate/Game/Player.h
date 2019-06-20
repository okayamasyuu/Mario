#pragma once
#include <Camera.h>
class Camera;
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
	CPad& pad = Pad(0);
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSoundSource* jump = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_charaCon; //キャラクターコントローラー
	Camera* camera = nullptr;
};

