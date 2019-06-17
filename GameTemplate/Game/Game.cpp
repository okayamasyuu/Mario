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

	return true;
}

void Game::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goaflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");


	if (m_goaflaag->GetClearFlag() == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			NewGO<title>(0);
			DeleteGO(this);
		}
	}

	if (m_pl->GetPosi().y < -200) {
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
