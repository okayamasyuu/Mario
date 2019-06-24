#pragma once
class Timer : public IGameObject
{
public:
	Timer();
	~Timer();
	bool Start();
	void Update();
	Game* ga;
private:
	prefab::CFontRender* m_fontRender = nullptr;
};

