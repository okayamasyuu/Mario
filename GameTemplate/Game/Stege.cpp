#include "stdafx.h"
#include "Stege.h"


Stege::Stege()
{
}


Stege::~Stege()
{
	DeleteGO(m_StegeModelRender);
}

bool Stege::Start()
{
	m_StegeModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_StegeModelRender->Init(L"modelData/stage.cmo");

	scela = { 2,2,2 };
	m_position = { 0,-300,0 };

	m_StegeModelRender->SetPosition(m_position);
	m_StegeModelRender->SetScale(scela);
	m_PSOject.CreateMesh(m_position, CQuaternion::Identity, scela, m_StegeModelRender);
	return true;
}
