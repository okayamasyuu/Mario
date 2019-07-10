#pragma once
class Score : public IGameObject
{
public:
	Score();
	~Score();
	bool Start();
	void Update();
	void TasuScore(int score)
	{
		Count += score;
	}
	int GetScore()
	{
		return Count;
	}
private:
	prefab::CFontRender* font = nullptr;
	int Count = 0;
};

