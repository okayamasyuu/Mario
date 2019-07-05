#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"

class Player;
class GoalFlaag;
class Enemy2 : public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	bool Start();
	void Update();
	void Turn();
	void GhostObj();
	CVector3 GetPosi()
	{
		return m_position;
	}
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
	}
	void SetScale(CVector3 Scale)
	{
		scale = Scale;
	}
	void SetRotation(CQuaternion rotation)
	{
		m_rot = rotation;
	}
	CVector3 Getscale()
	{
		return scale;
	}
	enum EnAnimationClip {
		enEnemy2AnimClip_walk,//歩きアニメーション
		enEnemy2AnimClip_Num
	};
private:
	Player* m_pl = nullptr;
	GoalFlaag* m_goalflaag = nullptr;
	prefab::CSkinModelRender* m_enemy2 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CCharacterController m_Enemy2CharaCon;
	CAnimationClip m_enemy2animClip[enEnemy2AnimClip_Num];
	CVector3 scale;
	//ゴーストオブジェクト
	CPhysicsGhostObject m_ghostobj;
	CVector3  ghostPosi = CVector3::Zero;
	CVector3 m_ghostmove = CVector3::Zero;
};

