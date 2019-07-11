#include "stdafx.h"
#include "GoalFlaag.h"
#include "Player.h"
#include "GameClear.h"
#include "title.h"
#include "Game.h"
#include "Result.h"
#include "Timer.h"
#include "Score.h"

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

	/*m_position.x = 300;
	m_position.y = -250;
	m_position.z = 1800;
	scela = { 5,5,5 };*/

	m_goalflaagModel->SetPosition(m_position);
	m_goalflaagModel->SetScale(scela);
	m_PSOject.CreateMesh(m_position, CQuaternion::Identity, scela, m_goalflaagModel);

	
	return true;
}
void GoalFlaag::Update()
{
	//�N���A���肵�ă��U���g��ʂ̃V�[���ɉf��
	if (Clear_flag == true) {
		QueryGOs<Game>("game", [&](Game * ga)->bool {
			ga->TasuTimer(5);
			if (ga->GetTimer() == 300) { //���U���g��ʂɈڂ�܂ł̃^�C��
				ga->SetTimer(0);
				Clear_flag = false;
				Result* re = NewGO<Result>(0, "���U���g");
				ti = FindGO<Timer>("����");
				sc = FindGO<Score>("�X�R�A");
				re->hunRe = ti->hun;
				re->byouRe = ti->byou;
				re->count = sc->Count;
				DeleteGO(ga);
				//NewGO<Result>(0, "���U���g");
			}
			return true;
		});
		
	}
	else {
		
		QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
			CVector3 diff = pl->GetPosi() - m_position;
			if (diff.Length() < 30.0f && Clear_flag == false) {
				/*ga->Clear_flag = true;*/
			
					NewGO<GameClear>(0, "�N���A");
					Clear_flag = true;



			}


			return true;
		});
	}
}