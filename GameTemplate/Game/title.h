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
	prefab::CSpriteRender* kabemozi = nullptr;
	prefab::CSoundSource* soundRender = nullptr;
	prefab::CSoundSource* APress = nullptr;
	CVector3 position = {-1000.0f, -20.0f, 0.0f};
	float time = 0.0f;
	float x = 0;
	float y = 0;
	
};

