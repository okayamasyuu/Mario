#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "title.h"
#include "Player.h"
#include "Camera.h"
#include "Stege.h"
#include "GameOver.h"
#include "GameClear.h"
#include "GoalFlaag.h"
#include "Enemy1.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO("プレイヤー");
	DeleteGO("カメラ");
	DeleteGOs("ステージ");
	DeleteGOs("ゲームオーバー");
	DeleteGOs("ゴールオブジェクト");
	DeleteGOs("クリア");
	DeleteGOs("敵１");
	DeleteGO(soundRender);
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	
	NewGO<Player>(0, "プレイヤー");
	NewGO<Camera>(0, "カメラ");
	NewGO<Stege>(0, "ステージ");
	NewGO<GoalFlaag>(0, "ゴールオブジェクト");
	//NewGO<Enemy1>(0, "敵１");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	return true;
}

void Game::Update()
{
	m_pl = FindGO<Player>("プレイヤー");
	m_goaflaag = FindGO<GoalFlaag>("ゴールオブジェクト");
	soundRender->Play(true);

	if (m_goaflaag->GetClearFlag() == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			soundRender->Stop();
			NewGO<title>(0);
			DeleteGO(this);
		}
	}

	if (m_pl->GetPosi().y < -200) {
		NewGO<GameOver>(0, "ゲームオーバー");
		m_timer += 5;
		if (m_timer == 500) {
			soundRender->Stop();
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
