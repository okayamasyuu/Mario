#include "stdafx.h"
#include "HaikeiWall.h"


HaikeiWall::HaikeiWall()
{
}


HaikeiWall::~HaikeiWall()
{
	DeleteGO(m_WallModelRender);
}
bool HaikeiWall::Start()
{
	m_WallModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_WallModelRender->Init(L"modelData/haikeiWall.cmo");

	m_WallModelRender->SetPosition(m_position);
	m_WallModelRender->SetScale(scela);
	return true;

}
