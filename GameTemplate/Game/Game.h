#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Player.h"

class Player;
class GoalFlaag;
class Enemy1;
class Enemy2;
class Block;
class Score;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	CLevel m_level;
	Player* m_pl = nullptr;
	GoalFlaag* m_goal = nullptr;
	Block* m_bl = nullptr;
	Enemy1* m_en1 = nullptr;
	Score* m_score = nullptr;
	/*Enemy1* en1[3] = { nullptr };
	Enemy2* en2[3] = { nullptr };*/
	//クラスの継承
	//ポイント型にする

	//静的メンバ変数
	static Game* m_instance;
	//インスタンスの取得
	static Game* GetInstance()
	{
		return m_instance;
	}

	void SetTimer(int time)
	{
		m_timer = time;
	}
	int GetTimer()
	{
		return m_timer;
	}
	void TasuTimer(int timer)
	{
		m_timer += timer;
	}
	float timer()const
	{
		return m_zikan;
	}
private:
	prefab::CDirectionLight* dirLight = nullptr;
	int m_timer = 0;
	prefab::CSoundSource* soundRender = nullptr;
	float m_zikan = 0.0f;
};

