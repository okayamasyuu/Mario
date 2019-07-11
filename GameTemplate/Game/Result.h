#pragma once
class Timer;
class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	prefab::CSpriteRender* m_resultSprite = nullptr;
	prefab::CFontRender* m_fontRender = nullptr;
	Timer* time = nullptr;
};

