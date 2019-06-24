#include "stdafx.h"
#include "Enemy1.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy1::Enemy1()
{
}


Enemy1::~Enemy1()
{
	DeleteGO(m_enemy);
}
bool Enemy1::Start()
{
	//�L�����R���̏�����
	m_EnemyCharaCon.Init(
		25.0,        //���a
		43.0,       //����
		m_position
	);

	////�G�i�m�R�m�R�j�̐��ii�j�@
	//for (int i = 0; i < 1; i++) {

	//	//�{�b�N�X�`��̃S�[�X�g�쐬����
	//	m_ghostobj.CreateBox(
	//		ghostPosi = m_position,    //�������͍��W�B
	//		CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
	//		{ 70.0, 10.0, 70.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
	//	);
	//}


	m_enemy = NewGO<prefab::CSkinModelRender>(0);
	//m_enemy->Init(L"modelData/Angel.cmo", m_enemyanimClip,enEnemyAnimClip_Num);
	m_enemy->Init(L"modelData/Angel.cmo");
	CVector3 scena = {
		4,
		4,
		4,

	};

	//m_enemyanimClip[enEnemyAnimClip_sky].Load(L"animData/angelmotion.tka");

	//m_enemyanimClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_position.y = 150;
	m_enemy->SetPosition(m_position);
	m_enemy->SetScale(scena);
	//m_enemy->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy1::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goalflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");

	m_position += m_moveSpeed;

	//�v���C���[��ǂ�������
	CVector3 toPlayer = { 0,0,0 };
	toPlayer = m_pl->GetPosi() - m_position;

	//toPlayer�̋������v�Z
	float len = toPlayer.Length();

	if (len < 50) {
		toPlayer.Normalize();
		//�X�s�[�h
		toPlayer.x *= 10;
		toPlayer.z *= 10;
		toPlayer.y *= 10;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		m_moveSpeed.y += toPlayer.y;
	}
	else {
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
		if (diff.Length() < 20 && m_goalflaag->GetClearFlag() == false
			&& pl->GetHP() > 0 && pl->GetMutekiFlag() == false) {
			//HP�_���[�W
			pl->HikuHP(1);
			//���G
			pl->SetMutekiFlag(true);
		}
		return true;
	});

	//�L�����R���Ɉړ����x��^����
	m_position = m_EnemyCharaCon.Execute(m_moveSpeed);

	//�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	m_enemy->SetPosition(m_EnemyCharaCon.GetPosition());

	Turn();

	m_enemy->SetRotation(m_rot);
}
void Enemy1::Turn()
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