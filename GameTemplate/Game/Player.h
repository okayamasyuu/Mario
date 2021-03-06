#pragma once
#include <Camera.h>
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Camera;
class Block;
class GoalFlaag;
class Enemy1;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Turn();
	void HPUI();
	void blink();
	void Coinget();
	void EnemyColider();
	void GhostObj();
	void SetScale(CVector3 Scale)
	{
		scale = Scale;
	}
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
	}
	CVector3 GetPosi()
	{
		return m_position;
	}
	int GetHP()
	{
		return HP;
	}
	void HikuHP(int hp)
	{
		HP -= hp;
	}
	void SetMutekiFlag(bool mutekiflag)
	{
		muteki = mutekiflag;
	}
	bool GetMutekiFlag()
	{
		return muteki;
	}
	//無敵時間
	void TasuMutekiTime(int timer)
	{
		mutekitime += timer;
	}
	int GetMutekiTime()
	{
		return mutekitime;
	}
	void SetMutekiTime(int timer)
	{
		mutekitime = timer;
	}
	void SetMoveSpeed(CVector3 movespeed)
	{
		m_moveSpeed.y = movespeed.y;
	}
	/*void Init(Block* p)

	{
		m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClips, enAnimationClip_Num);
		parent = p;
	}
	void SetWorldMatrix(CMatrix World)
	{
		 worldMatrix = World;
	}*/
	CMatrix worldMatrix;			//ワールド行列。
	CCharacterController m_charaCon; //キャラクターコントローラー
	CPad& pad = Pad(0);
	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション。
		//enAnimationClip_run,	//走りアニメーション。
		enAnimationClip_walk,   //歩きアニメーション
		enAnimationClip_jump,   //ジャンプアニメーション
		enAnimationClip_Num,	//アニメーションクリップの数。
	};
	prefab::CSpriteRender* HPmae = nullptr;
private:
	Block* parent = nullptr;//親
	CVector3 scale;
	int m_state = 0; //状態の変数
	int HP = 10;
	int count = 0;
	bool  muteki = false;
	int mutekitime = 0;
	prefab::CFontRender* font = nullptr; //フォント
	prefab::CSpriteRender* HPusiro = nullptr;
	
	float m_moveSpeedWhenStartJump;			//ジャンプを開始したときの移動速度。
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CAnimationClip m_animClips[enAnimationClip_Num];
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 HPmaePos = { 200.0f, 250.0f , 0.0f };
	CVector3 HPusiroPos = { 200.0f, 100.0f , 0.0f };
	CVector4 color = CVector4::Yellow;
	Camera* camera = nullptr;
	Block* m_bl = nullptr;
	GoalFlaag* m_goal = nullptr;
	Enemy1* m_en1 = nullptr;

	//ゴーストオブジェクト
	CPhysicsGhostObject m_ghostobj;
	CVector3  ghostPosi = CVector3::Zero;
};

