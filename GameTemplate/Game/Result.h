#pragma once
class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	prefab::CSpriteRender* m_resultSprite = nullptr;
};

