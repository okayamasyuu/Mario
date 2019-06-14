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
	m_StegeModelRender->Init(L"modelData/yuka.cmo");

	scela = { 7,3,7 };
	m_position = { 0,-10,0 };

	m_StegeModelRender->SetPosition(m_position);
	m_StegeModelRender->SetScale(scela);
	m_PSOject.CreateMesh(m_position, CQuaternion::Identity, scela, m_StegeModelRender);
	return true;
}
