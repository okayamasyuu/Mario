#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"

class Player;
class GoalFlaag;

class Enemy1 : public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	bool Start();
	void Update();
	void Turn();
	void GhostObj();
	enum EnAnimationClip {
		enEnemyAnimClip_sky,//��s�A�j���[�V����
		enEnemyAnimClip_Num
	};
private:
	Player* m_pl = nullptr;
	GoalFlaag* m_goalflaag = nullptr;
	CAnimationClip m_enemyanimClip[enEnemyAnimClip_Num];
	prefab::CSkinModelRender* m_enemy = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CCharacterController m_EnemyCharaCon;

	//�S�[�X�g�I�u�W�F�N�g
	CPhysicsGhostObject m_ghostobj; 
	CVector3  ghostPosi = CVector3::Zero;
	CVector3 m_ghostmove = CVector3::Zero;
};

