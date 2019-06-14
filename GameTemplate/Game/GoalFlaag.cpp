#include "stdafx.h"
#include "GoalFlaag.h"
#include "Player.h"
#include "GameClear.h"
#include "title.h"
#include "Game.h"

GoalFlaag::GoalFlaag()
{
}


GoalFlaag::~GoalFlaag()
{
	DeleteGO(m_goalflaagModel);
}
bool GoalFlaag::Start()
{
	m_goalflaagModel = NewGO<prefab::CSkinModelRender>(0);
	m_goalflaagModel->Init(L"modelData/hatahata.cmo");	//�S�[���I�u�W�F�N�g

	m_position.x = 100;

	m_goalflaagModel->SetPosition(m_position);
	m_goalflaagModel->SetScale(scela);

	return true;
}
void GoalFlaag::Update()
{
	//�N���A���肵�ă��U���g��ʂ̃V�[���ɉf��
	QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		if (diff.Length() < 100.0f) {
			/*Game* ga = FindGO<Game>("game");
			ga->Clear_flag = true;*/
			NewGO<GameClear>(0, "�N���A");
			//ga->m_timer += 5;
			if (ga->GetTimer() == 300) {
				ga->SetTimer(0);
				//NewGO<title>(0);
				DeleteGO(ga);
			}
		}


		return true;
	});
}