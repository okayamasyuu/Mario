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
#include "coin.h"

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

	//playerの頭当たりに（真上）に敵が当たると強制的にゲームオーバーになって挙動がおかしくなる
	//またはエラーが出る　コリジョンわけわかめなので勘弁してください。
	//他の部分からの当たり判定は正常
	//なのでenemy1の追跡範囲と位置を低めにしました

	/*
	クラス　プレイヤー、ステージ、ゴール、敵１、敵２、ブロック、コインを
　　NewGOしているところをコメントアウトする
	クラスの中で座標や大きさをSetしていたらコメントアウトする
	ファイルパス Mariotkl
	Angel
	WorkEnemy
	unityChan　
	stage   
	hatahata　
	block　　　
	coin 　　　
	*/
	m_level.Init(L"Mariotkl.tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "プレイヤー");
			pl->SetPosi(objData.position);
			pl->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"hatahata")){
			GoalFlaag* goal = NewGO<GoalFlaag>(0, "ゴールオブジェクト");
			goal->SetPosi(objData.position);
			goal->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"stage")){
			Stege* st  = NewGO<Stege>(0, "ステージ");
			st->SetPosi(objData.position);
			st->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"block")){
			Block* bl  = NewGO<Block>(0, "ブロック");
			bl->SetPosi(objData.position);
			bl->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"koin")){
			Coin* co  = NewGO<Coin>(0, "コイン");
			co->SetPosi(objData.position);
			co->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"Angel")) {
			Enemy1* en1 = NewGO<Enemy1>(0, "敵1");
			en1->SetPosi(objData.position);
			en1->SetScale(objData.scale);
			en1->SetRotation(objData.rotation);
			return true;
		}
		else if (objData.EqualObjectName(L"WorkEnemy")) {
			Enemy2* en2 = NewGO<Enemy2>(0, "敵2");
			en2->SetPosi(objData.position);
			en2->SetScale(objData.scale);
			en2->SetRotation(objData.rotation);
			return true;
		}
	});

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
	DeleteGOs("敵1");
	DeleteGOs("敵2");
	DeleteGO(soundRender);
	DeleteGO("時間");
	DeleteGOs("ブロック");
	DeleteGOs("コイン");
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	
	//NewGO<Player>(0, "プレイヤー");
	NewGO<Camera>(0, "カメラ");
	//NewGO<Stege>(0, "ステージ");
	//NewGO<GoalFlaag>(0, "ゴールオブジェクト");

	/*en1[0]=NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -150,-250,300 });
	en1[0] = NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -250,-250,400 });
	en1[0] = NewGO<Enemy1>(0, "敵１");
	en1[0]->SetPosi({ -350,-250,700 });*/

	//NewGO<Enemy2>(0, "敵2");
	//NewGO<Enemy1>(0, "敵１");
	NewGO<Timer>(0, "時間");
	//NewGO<Block>(0, "ブロック");
	//NewGO<Coin>(0, "コイン");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	soundRender->SetVolume(10.0f);
	return true;
}

void Game::Update()
{
	m_zikan = min(999.0f, m_zikan + GameTime().GetFrameDeltaTime());
	m_pl = FindGO<Player>("プレイヤー");
	m_goal = FindGO<GoalFlaag>("ゴールオブジェクト");
	soundRender->Play(true);

	if (m_goal->GetClearFlag() == false) {
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
		soundRender->Stop();
		NewGO<GameOver>(0, "ゲームオーバー");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
