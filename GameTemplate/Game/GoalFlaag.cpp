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
	m_goalflaagModel->Init(L"modelData/hatahata.cmo");	//ゴールオブジェクト

	m_position.x = 100;

	m_goalflaagModel->SetPosition(m_position);
	m_goalflaagModel->SetScale(scela);

	return true;
}
void GoalFlaag::Update()
{
	//クリア判定してリザルト画面のシーンに映る
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		if (diff.Length() < 100.0f) {
			/*Game* ga = FindGO<Game>("game");
			ga->Clear_flag = true;*/
			NewGO<GameClear>(0, "クリア");
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