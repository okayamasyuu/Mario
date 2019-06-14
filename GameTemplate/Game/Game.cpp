#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "title.h"
#include "Player.h"
#include "Camera.h"
#include "Stege.h"

CVector3 cameraPos = { 0.0f, 70.0f, 200.0f };
CVector3 cameraTarget;
Game::Game()
{
}


Game::~Game()
{
	DeleteGO("プレイヤー");
	DeleteGO("カメラ");
	DeleteGOs("ステージ");
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	NewGO<Player>(0, "プレイヤー");
	NewGO<Camera>(0, "カメラ");
	NewGO<Stege>(0, "ステージ");
	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonSelect) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}


}
