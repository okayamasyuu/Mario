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
#include "Block.h"

//唯一のインスタンスのアドレスを記録するポインタ変数。 
//静的メンバ変数を定義する
Game* Game::m_instance = nullptr;
Game::Game()
{

	if (m_instance != nullptr) {   
		//すでにインスタンスを作っている。 
		std::abort();  
	}
	//このインスタンスを唯一のインスタンスとして記録する。 
	m_instance = this; 


	/*
	クラス　プレイヤー、ステージ、ゴール、敵１、敵２、ブロックを
　　NewGOしているところをコメントアウトする
	クラスの中で座標や大きさをSetしていたらコメントアウトする
	ファイルパス STAGE
	Angel
	WorkEnemy
	unityChan　座標
	stge_1   座標
	hatahata　座標
	block　　　座標
	まだですcoin 　　　大きさ　座標、(回転あってもなくても)
	*/
	/*m_level.Init(L"STAGE.tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "プレイヤー");
			pl->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"hatahata")){
			GoalFlaag* goal = NewGO<GoalFlaag>(0, "ゴールオブジェクト");
			goal->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"stge_1")){
			Stege* st  = NewGO<Stege>(0, "ステージ");
			st->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"block")){
			Block* bl  = NewGO<Block>(0, "ブロック");
			bl->SetPosi(objData.position);
			return true;
		}
	});*/

}


Game::~Game()
{
	//インスタンスが破棄されたので、nullptrを代入する。  
	m_instance = nullptr;

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
	DeleteGOs("ブロック");
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

	en1[0]=NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -150,-250,300 });
	en1[0] = NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -250,-250,400 });
	en1[0] = NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -350,-250,700 });

	NewGO<Enemy2>(0, "敵2");
	//NewGO<Enemy1>(0, "敵１");
	NewGO<Timer>(0, "時間");
	NewGO<Block>(0, "ブロック");
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
