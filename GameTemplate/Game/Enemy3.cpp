#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"
#include "GoalFlaag.h"

Enemy3::Enemy3()
{
}


Enemy3::~Enemy3()
{
	DeleteGO(m_enemy3);
}
bool Enemy3::Start()
{
	//m_enemy3animClip[enEnemyAnimClip_sky].Load(L"animData/WorkEnemymotion.tka");

	//m_enemy3animClip[enEnemyAnimClip_sky].SetLoopFlag(true);

	m_enemy3 = NewGO<prefab::CSkinModelRender>(0);
	//m_enemy3->Init(L"modelData/Angel.cmo", m_enemy3animClip, enEnemyAnimClip_Num);

	m_enemy3->Init(L"modelData/Angel.cmo");


	m_EnemyCharaCon.Init(
		10.0,        //���a
		10.0,       //����
		m_position
	);

	for (int i = 0; i < 1; i++) {

		//�{�b�N�X�`��̃S�[�X�g�쐬����
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //�������͍��W�B
			CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
			{ 12.0, 5.0, 12.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
		);
	}

	m_moveSpeed.y = 150;
	m_enemy3->SetShadowCasterFlag(true);

	m_enemy3->SetPosition(m_position);
	m_enemy3->SetScale(scena);
	m_enemy3->SetRotation(m_rot);
	//m_enemy3->PlayAnimation(enEnemyAnimClip_sky);
	return true;
}
void Enemy3::Update()
{
	m_pl = FindGO<Player>("�v���C���[");
	m_goalflaag = FindGO<GoalFlaag>("�S�[���I�u�W�F�N�g");

	m_position += m_moveSpeed;

	//�㉺�Ɉړ�
	timer++;
	
	if (timer >= 20 ){
		timer = 0;
	    m_moveSpeed.y *= -1.0;//��
	}
	if (timer >= 20 && m_moveSpeed.y < 0) {
		m_moveSpeed.y *= 1.0;//��
	}

	GhostObj();

	//�L�����R���Ɉړ����x��^����
	m_position = m_EnemyCharaCon.Execute(m_moveSpeed);

	//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
	CVector3 pos = m_position;
	pos.y += 30;
	m_ghostobj.SetPosition(pos);

	////�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	m_enemy3->SetPosition(m_EnemyCharaCon.GetPosition());

}
void Enemy3::GhostObj()
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