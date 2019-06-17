#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Player.h"

class Player;
class GoalFlaag;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	
	Player* m_pl = nullptr;
	GoalFlaag* m_goaflaag = nullptr;
	//クラスの継承
	//ポイント型にする

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
private:
	int m_timer = 0;
};

