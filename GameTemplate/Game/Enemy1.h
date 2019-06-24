#pragma once
class Enemy1 : public IGameObject
{
public:
	Enemy1();
	~Enemy1();
	bool Start();
	void Update();
	enum EnAnimationClip {
		enEnemyAnimClip_sky,//飛行アニメーション
		enEnemyAnimClip_Num
	};
private:
	CAnimationClip m_enemyanimClip[enEnemyAnimClip_Num];
	prefab::CSkinModelRender* m_enemy = nullptr;
	CVector3 m_position = CVector3::Zero;
};

