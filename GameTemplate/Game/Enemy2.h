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
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
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

	//ゴーストオブジェクト
	CPhysicsGhostObject m_ghostobj;
	CVector3  ghostPosi = CVector3::Zero;
	CVector3 m_ghostmove = CVector3::Zero;
};

