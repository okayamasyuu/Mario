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

	//player�̓�������Ɂi�^��j�ɓG��������Ƌ����I�ɃQ�[���I�[�o�[�ɂȂ��ċ��������������Ȃ�
	//�܂��̓G���[���o��@�R���W�����킯�킩�߂Ȃ̂Ŋ��ق��Ă��������B
	//���̕�������̓����蔻��͐���
	//�Ȃ̂�enemy1�̒ǐՔ͈͂ƈʒu���߂ɂ��܂���

	/*
	�N���X�@�v���C���[�A�X�e�[�W�A�S�[���A�G�P�A�G�Q�A�u���b�N�A�R�C����
�@�@NewGO���Ă���Ƃ�����R�����g�A�E�g����
	�N���X�̒��ō��W��傫����Set���Ă�����R�����g�A�E�g����
	�t�@�C���p�X Mariotkl
	Angel
	WorkEnemy
	unityChan�@
	stage   
	hatahata�@
	block�@�@�@
	coin �@�@�@
	*/
	m_level.Init(L"Mariotkl.tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "�v���C���[");
			pl->SetPosi(objData.position);
			pl->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"hatahata")){
			GoalFlaag* goal = NewGO<GoalFlaag>(0, "�S�[���I�u�W�F�N�g");
			goal->SetPosi(objData.position);
			goal->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"stage")){
			Stege* st  = NewGO<Stege>(0, "�X�e�[�W");
			st->SetPosi(objData.position);
			st->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"block")){
			Block* bl  = NewGO<Block>(0, "�u���b�N");
			bl->SetPosi(objData.position);
			bl->SetScale(objData.scale);
			return true;
		}
		else if(objData.EqualObjectName(L"koin")){
			Coin* co  = NewGO<Coin>(0, "�R�C��");
			co->SetPosi(objData.position);
			co->SetScale(objData.scale);
			return true;
		}
		else if (objData.EqualObjectName(L"Angel")) {
			Enemy1* en1 = NewGO<Enemy1>(0, "�G1");
			en1->SetPosi(objData.position);
			en1->SetScale(objData.scale);
			en1->SetRotation(objData.rotation);
			return true;
		}
		else if (objData.EqualObjectName(L"WorkEnemy")) {
			Enemy2* en2 = NewGO<Enemy2>(0, "�G2");
			en2->SetPosi(objData.position);
			en2->SetScale(objData.scale);
			en2->SetRotation(objData.rotation);
			return true;
		}
	});

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
	DeleteGOs("�G1");
	DeleteGOs("�G2");
	DeleteGO(soundRender);
	DeleteGO("����");
	DeleteGOs("�u���b�N");
	DeleteGOs("�R�C��");
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	
	//NewGO<Player>(0, "�v���C���[");
	NewGO<Camera>(0, "�J����");
	//NewGO<Stege>(0, "�X�e�[�W");
	//NewGO<GoalFlaag>(0, "�S�[���I�u�W�F�N�g");

	/*en1[0]=NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -150,-250,300 });
	en1[0] = NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -250,-250,400 });
	en1[0] = NewGO<Enemy1>(0, "�G�P");
	en1[0]->SetPosi({ -350,-250,700 });*/

	//NewGO<Enemy2>(0, "�G2");
	//NewGO<Enemy1>(0, "�G�P");
	NewGO<Timer>(0, "����");
	//NewGO<Block>(0, "�u���b�N");
	//NewGO<Coin>(0, "�R�C��");
	soundRender = NewGO<prefab::CSoundSource>(0);
	soundRender->Init(L"sound/field1.wav");
	soundRender->SetVolume(10.0f);
	return true;
}

void Game::Update()
{
	m_zikan = min(999.0f, m_zikan + GameTime().GetFrameDeltaTime());
	m_pl = FindGO<Player>("�v���C���[");
	m_goal = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");
	soundRender->Play(true);

	if (m_goal->GetClearFlag() == false) {
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
		soundRender->Stop();
		NewGO<GameOver>(0, "�Q�[���I�[�o�[");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			m_timer = 0;
		}
	}
}
