#pragma once
class title : public IGameObject
{
public:
	title();
	~title();
	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
};

