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

	int Count = 0;
private:
	prefab::CFontRender* font = nullptr;
	
};

