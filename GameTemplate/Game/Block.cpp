#include "stdafx.h"
#include "Block.h"


Block::Block()
{
}


Block::~Block()
{
	DeleteGO(m_block);
}
bool Block::Start()
{
	m_block = NewGO<prefab::CSkinModelRender>(0);
	m_block->Init(L"modelData/block.cmo");
	//m_position = { 200,-90,0 };
	//scale = { 2,2,2 };
	m_block->SetPosition(m_position);
	m_block->SetScale(scale);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_block);
	return true;
}
void Block::Update()
{

}