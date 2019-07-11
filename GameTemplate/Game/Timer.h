#pragma once

class Game;
class Timer : public IGameObject
{
public:
	Timer();
	~Timer();
	bool Start() override;
	void Update() override;
	float hun, byou;
private:
	prefab::CFontRender* m_fontRender = nullptr;
	//Game* ga = nullptr;
};

