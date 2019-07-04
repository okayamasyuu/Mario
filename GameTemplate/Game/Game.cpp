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

//�B��̃C���X�^���X�̃A�h���X���L�^����|�C���^�ϐ��B 
//�ÓI�����o�ϐ����`����
Game* Game::m_instance = nullptr;
Game::Game()
{

	if (m_instance != nullptr) {   
		//���łɃC���X�^���X������Ă���B 
		std::abort();  
	}
	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����B 
	m_instance = this; 


	/*
	�N���X�@�v���C���[�A�X�e�[�W�A�S�[���A�G�P�A�G�Q�A�u���b�N��
�@�@NewGO���Ă���Ƃ�����R�����g�A�E�g����
	�N���X�̒��ō��W��傫����Set���Ă�����R�����g�A�E�g����
	�t�@�C���p�X STAGE
	Angel
	WorkEnemy
	unityChan�@���W
	stge_1   ���W
	hatahata�@���W
	block�@�@�@���W
	�܂��ł�coin �@�@�@�傫���@���W�A(��]�����Ă��Ȃ��Ă�)
	*/
	/*m_level.Init(L"STAGE.tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "�v���C���[");
			pl->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"hatahata")){
			GoalFlaag* goal = NewGO<GoalFlaag>(0, "�S�[���I�u�W�F�N�g");
			goal->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"stge_1")){
			Stege* st  = NewGO<Stege>(0, "�X�e�[�W");
			st->SetPosi(objData.position);
			return true;
		}
		else if(objData.EqualObjectName(L"block")){
			Block* bl  = NewGO<Block>(0, "�u���b�N");
			bl->SetPosi(objData.position);
			return true;
		}
	});*/

}


Game::~Game()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr��������B  
	m_instance = nullptr;

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
	en1[0]->SetPosi({ -250,-250,400 });
	en1[0] = NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -350,-250,700 });

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
