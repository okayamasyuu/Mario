#pragma once
class Timer;
class Score;
class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	prefab::CSpriteRender* m_resultSprite = nullptr;
	prefab::CFontRender* m_fontRender = nullptr;
	prefab::CFontRender* font = nullptr;
	Timer* time = nullptr;
	Score* sc = nullptr;
	
	float hunRe, byouRe;
	int count;
	
};

