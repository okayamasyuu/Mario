#pragma once
class title : public IGameObject
{
public:
	title();
	~title();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSoundSource* soundRender = nullptr;
	prefab::CSoundSource* APress = nullptr;
};

