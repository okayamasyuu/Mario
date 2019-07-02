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

Game::Game()
{
	/*
	STAGE
	unityChan
	stge_1
	hatahata
	Angel
	WorkEnemy
	
	*/
	/*m_level.Init(L".tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "�v���C���[");
			pl->GetPosi() = objData.position;
			return true;
		}

	});*/
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
	DeleteGOs("�G2");
	DeleteGO(soundRender);
	DeleteGO("����");
	DeleteGOs("�u���b�N");
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

	en1[0]=NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -150,-250,300 });
	en1[0] = NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -250,-250,300 });
	en1[0] = NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -350,-250,300 });

	NewGO<Enemy2>(0, "�G2");
	//NewGO<Enemy1>(0, "�G�P");
	NewGO<Timer>(0, "����");
	NewGO<Block>(0, "�u���b�N");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	soundRender->SetVolume(10.0f);
	return true;
}

void Game::Update()
{
	m_zikan = min(999.0f, m_zikan + GameTime().GetFrameDeltaTime());
	m_pl = FindGO<Player>("�v���C���[");
	m_goaflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");
	soundRender->Play(true);

	if (m_goaflaag->GetClearFlag() == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			soundRender->Stop();
			//NewGO<GameClear>(0, "�N���A");
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
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
	//HP0
	if (m_pl->GetHP() <= 0) {
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
