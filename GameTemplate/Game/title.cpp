#include "stdafx.h"
#include "title.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

title::title()
{
}


title::~title()
{
	DeleteGO(kabemozi);
	DeleteGO(m_spriteRender);
	DeleteGO(soundRender);
}
bool title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Mario.Titlehaikei2.dds", 1280.0f, 720.0f);
	kabemozi = NewGO<prefab::CSpriteRender>(0);
	kabemozi->Init(L"sprite/Mario.Titlemozi.dds", 1000.0f, 800.0f);
	kabemozi->SetPosition(position);
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/taitle1.wav");
	APress = NewGO<prefab::CSoundSource>(0);
	APress->Init(L"sound/nanndeyanen.wav");
	APress->SetVolume(30.0f);
	
	return true;
}
void title::Update()
{
	time += GameTime().GetFrameDeltaTime();
	if (time <= 3.0f) {
		x += 0.5;
		position.x += x;
	}
	if (time >= 3.0f) {
		x = 0;
		y += 0.5;
		position.x -= y;
		if (position.x <= -100.0f) {
			float z = -150.0f;
			position.x = z;
		}
	}
	
	soundRender->Play(true);
	if (Pad(0).IsTrigger(enButtonA)) {
		soundRender->Stop();
		APress->Play(false);
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
	kabemozi->SetPosition(position);
}