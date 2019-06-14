#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Player.h"

class Player;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	
	Player* m_pl = nullptr;
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
	int TasuTimer(int time)
	{
		m_timer += time;
	}
private:
	int m_timer = 0;
};

