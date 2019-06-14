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
	DeleteGO("�v���C���[");
	DeleteGO("�J����");
	DeleteGOs("�X�e�[�W");
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	NewGO<Player>(0, "�v���C���[");
	NewGO<Camera>(0, "�J����");
	NewGO<Stege>(0, "�X�e�[�W");
	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonSelect) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}


}
