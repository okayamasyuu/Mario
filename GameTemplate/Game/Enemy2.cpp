#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy2::Enemy2()
{
}


Enemy2::~Enemy2()
{
	DeleteGO(m_enemy2);
}
bool Enemy2::Start()
{
	m_enemy2animClip[enEnemy2AnimClip_walk].Load(L"animData/WorkEnemymotion.tka");

	m_enemy2animClip[enEnemy2AnimClip_walk].SetLoopFlag(true);


	m_enemy2 = NewGO<prefab::CSkinModelRender>(0);
	m_enemy2->Init(L"modelData/WorkEnemy.cmo", m_enemy2animClip, enEnemy2AnimClip_Num);
	
	CVector3 scale = { 4,4,4 };

	m_position.x = -400;
	m_position.y = -200;

	//�L�����R���̏�����
	m_Enemy2CharaCon.Init(
		25.0,        //���a
		47.0,       //����
		m_position
	);
	
	for (int i = 0; i < 1; i++) {

		//�{�b�N�X�`��̃S�[�X�g�쐬����
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //�������͍��W�B
			CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
			{ 40.0, 5.0, 40.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
		);
	}
	
	m_enemy2->SetPosition(m_position);
	m_enemy2->SetScale(scale);
	//m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
	return true;
}
void Enemy2::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goalflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");

	//�N���{�[�̃V�X�e��

	m_position += m_moveSpeed;

	//�v���C���[��ǂ�������
	CVector3 toPlayer = { 0,0,0 };
	toPlayer = m_pl->GetPosi() - m_position;

	//toPlayer�̋������v�Z
	float len = toPlayer.Length();

	//�͈�
	if (len < 300) {
		toPlayer.Normalize();
		//�X�s�[�h
		toPlayer.x *= 10;
		toPlayer.z *= 10;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		if (m_moveSpeed.LengthSq() > 10 * 10) {
			m_enemy2->PlayAnimation(enEnemy2AnimClip_walk);
		}
	}
	else {
		toPlayer.x *= 0;
		toPlayer.z *= 0;
		m_moveSpeed.x = toPlayer.x;
		m_moveSpeed.z = toPlayer.z;
	}

	//HP�_���[�W
	QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		CVector3 diff = pl->GetPosi() - m_position;
		//���G����
		if (pl->GetMutekiFlag() == true) {
			pl->TasuMutekiTime(1);
			if (pl->GetMutekiTime() == 100) {
				pl->SetMutekiFlag(false);
				pl->SetMutekiTime(0);
			}
		}

		//�����������Ȃ�����
		//����0.5�O�ギ�炢
		if (diff.Length() < 0.27 && m_goalflaag->GetClearFlag() == false
			&& pl->GetHP() > 0 && pl->GetMutekiFlag() == false) {
			//HP�_���[�W
			pl->HikuHP(1);
			//���G
			pl->SetMutekiFlag(true);
		}
		return true;
	});

	GhostObj();

	//�d��
	m_moveSpeed.y -= 700.0 * GameTime().GetFrameDeltaTime();

	//�L�����R���Ɉړ����x��^����
	m_position = m_Enemy2CharaCon.Execute(m_moveSpeed);
	
	//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
	CVector3 pos = m_position;	
	pos.y += 120;
	m_ghostobj.SetPosition(pos);

	//�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	m_enemy2->SetPosition(m_Enemy2CharaCon.GetPosition());

	Turn();

	m_enemy2->SetRotation(m_rot);
}
void Enemy2::Turn()
{
	//Enemy�̉�]
	if (fabsf(m_moveSpeed.x) < 0.001f &&
		fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//�p�x�����߂Ă���
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	//Y����]
	m_rot.SetRotation(CVector3::AxisY, angle);
}
void Enemy2::GhostObj()
{
	//�S�[�X�g�I�u�W�F�N�g�̓����蔻��(�v���C���[)
	PhysicsWorld().ContactTest(m_pl->m_charaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {
			//���񂾂���
			m_pl->SetMoveSpeed({ 0,300,0 });
			DeleteGO(this); //����������j��
		}
	});
}