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
	
	m_enemyanimClip[enEnemyAnimClip_sky].Load(L"animData/angelmotion.tka");

	m_enemyanimClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_enemy = NewGO<prefab::CSkinModelRender>(0);
	m_enemy->Init(L"modelData/Angel.cmo", m_enemyanimClip,enEnemyAnimClip_Num);
	//m_enemy->Init(L"modelData/Angel.cmo");
	 scena = {
		4,
		4,
		4,

	};
	//�G1�̃|�W�V�����ʒu�A�z��
	/*m_position.y = -250;
	m_position.x = -150;
	m_position.z = 350;*/
	//�L�����R���̏�����
	m_EnemyCharaCon.Init(
		25.0,        //���a
		43.0,       //����
		m_position
	);

	//�G�i�m�R�m�R�j�̐��ii�j�@
	for (int i = 0; i < 1; i++) {

		//�{�b�N�X�`��̃S�[�X�g�쐬����
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //�������͍��W�B
			CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
			{ 30.0, 5.0, 30.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
		);
	}

	m_enemy->SetPosition(m_position);
	m_enemy->SetScale(scena);
	m_enemy->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy1::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goalflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");

	//�Q�[���̃N���X�̃|�C���^��Ԃ�
	//m_pl = Game::GetInstance()->m_pl;
	//m_goalflaag = Game::GetInstance()->m_goaflaag;

	m_position += m_moveSpeed;

	GhostObj();

	CQuaternion Rot;
	Rot.SetRotationDeg(
		{ 0.0f, 1.0, 0.0 },
		3.0f);
	m_rot *= Rot;
	
	CVector3 toPlayer = { 0,0,0 };

	/////////����p
	CVector3 enemyForward = CVector3::AxisZ;
	m_rot.Multiply(enemyForward);

	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayerDir = m_pl->GetPosi() - m_position;
	//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K���I
	toPlayerDir.Normalize();
	//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = enemyForward.Dot(toPlayerDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	//����p����
	//fabsf�͐�Βl�����߂�֐��I
	//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
	if (fabsf(angle) < CMath::DegToRad(45.0f)
		&& toPlayerLen < 400.0f)
	{
		//�v���C���[��ǂ�������
		
		toPlayer = m_pl->GetPosi() - m_position;

		//toPlayer�̋������v�Z
		float len = toPlayer.Length();
		toPlayer.Normalize();
		//�X�s�[�h
		toPlayer.x *= 12;
		toPlayer.z *= 12;
		toPlayer.y *= 12;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		m_moveSpeed.y += toPlayer.y;
	}


	//�͈�
	//if (len < 500) {
	//	toPlayer.Normalize();
	//	//�X�s�[�h
	//	toPlayer.x *= 10;
	//	toPlayer.z *= 10;
	//	toPlayer.y *= 10;
	//	m_moveSpeed.x += toPlayer.x;
	//	m_moveSpeed.z += toPlayer.z;
	//	m_moveSpeed.y += toPlayer.y;
	//	
	//}
	else {
		toPlayer = { 0,0,0 };
		m_moveSpeed = toPlayer;
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
		if (diff.Length() < 1.2 && m_goalflaag->GetClearFlag() == false
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

	//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
	CVector3 pos = m_position;
	pos.y += 90;
	m_ghostobj.SetPosition(pos);

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
void Enemy1::GhostObj()
{
	
	//�S�[�X�g�I�u�W�F�N�g�̓����蔻��(�v���C���[)
	PhysicsWorld().ContactTest(m_pl->m_charaCon,[&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {
			//���񂾂���
			m_pl->SetMoveSpeed({ 0,300,0 });
			DeleteGO(this); //����������j��
		}
	});
	
}