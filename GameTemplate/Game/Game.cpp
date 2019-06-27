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
#include "Timer.h"

#include"Enemy2.h"
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
	DeleteGOs("敵2");
	DeleteGO(soundRender);
	DeleteGO("時間");
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
	NewGO<Enemy1>(0, "敵１");
	NewGO<Enemy2>(0, "敵2");
	//NewGO<Enemy1>(0, "敵１");
	NewGO<Timer>(0, "時間");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	soundRender->SetVolume(10.0f);
	return true;
}

void Game::Update()
{
	m_zikan = min(999.0f, m_zikan + GameTime().GetFrameDeltaTime());
	m_pl = FindGO<Player>("プレイヤー");
	m_goaflaag = FindGO<GoalFlaag>("ゴールオブジェクト");
	soundRender->Play(true);

	if (m_goaflaag->GetClearFlag() == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			soundRender->Stop();
			//NewGO<GameClear>(0, "クリア");
			//m_timer += 5;
			//if (m_timer == 500) {
				DeleteGO(this);
				NewGO<title>(0);
				m_timer = 0;
			//}
		}
	}

	if (m_pl->GetPosi().y < -1500) {
		soundRender->Stop();
		NewGO<GameOver>(0, "ゲームオーバー");
		m_timer += 5;
		if (m_timer == 500) {
			
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
	//HP0
	if (m_pl->GetHP() <= 0) {
		NewGO<GameOver>(0, "ゲームオーバー");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
