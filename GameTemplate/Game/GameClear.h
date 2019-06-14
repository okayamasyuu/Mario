#pragma once
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_gameClearSprite = nullptr;

};

