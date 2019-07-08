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

	//m_skinModelData.Load(L"modelData/block.cmo");
	//block_model.Init(m_skinModelData);


	//m_position = { 200,-90,0 };
	//scale = { 2,2,2 };
	m_moveSpeed = { 4,0,0 };
	m_block->SetPosition(m_position);
	m_block->SetScale(scale);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_block);
	return true;
}
void Block::Update()
{
	/*m_position += m_moveSpeed;

	timer++;
	if (timer == 100) {
		m_moveSpeed *= -1.0;
		timer = 0;
	}
	
	m_block->SetPosition(m_position);*/
}