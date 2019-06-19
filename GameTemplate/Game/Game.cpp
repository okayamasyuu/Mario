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
	DeleteGO("�v���C���[");
	DeleteGO("�J����");
	DeleteGOs("�X�e�[�W");
	DeleteGOs("�Q�[���I�[�o�[");
	DeleteGOs("�S�[���I�u�W�F�N�g");
	DeleteGOs("�N���A");
	DeleteGOs("�G�P");
	DeleteGO(soundRender);
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	
	NewGO<Player>(0, "�v���C���[");
	NewGO<Camera>(0, "�J����");
	NewGO<Stege>(0, "�X�e�[�W");
	NewGO<GoalFlaag>(0, "�S�[���I�u�W�F�N�g");
	//NewGO<Enemy1>(0, "�G�P");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	return true;
}

void Game::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goaflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");
	soundRender->Play(true);

	if (m_goaflaag->GetClearFlag() == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			soundRender->Stop();
			NewGO<title>(0);
			DeleteGO(this);
		}
	}

	if (m_pl->GetPosi().y < -200) {
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			soundRender->Stop();
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
