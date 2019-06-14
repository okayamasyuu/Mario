#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;

};

