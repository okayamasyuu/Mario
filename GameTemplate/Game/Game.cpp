#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "title.h"
#include "Player.h"
#include "Camera.h"
#include "Stege.h"
#include "GameOver.h"

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
	DeleteGOs("�Q�[���I�[�o�[");
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
	m_pl = FindGO<Player>("�v���C���[");

	if (Pad(0).IsPress(enButtonSelect) == true) {
		NewGO<title>(0);
		DeleteGO(this);
	}

	if (m_pl->GetPosi().y < -100) {
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
