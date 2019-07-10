#include "stdafx.h"
#include "Player.h"
#include "Block.h"
#include "Game.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "GoalFlaag.h"

Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(font);
	DeleteGO(HPmae);
	DeleteGO(HPusiro);
}

bool Player::Start()
{
	//���C���[�t���[���\����L���ɂ���
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	//m_position.y = -250;
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		10.0,        //���a �傫��
		20.0,       //����
		m_position
	);
	
	//for (int i = 0; i < 1; i++) {

	//	//�{�b�N�X�`��̃S�[�X�g�쐬����
	//	m_ghostobj.CreateBox(
	//		ghostPosi = m_position,    //�������͍��W�B
	//		CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
	//		{ 12.0, 4.0, 12.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
	//	);
	//}
	//HPUI
	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Black);


	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClips[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClips[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClips[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->PlayAnimation(enAnimationClip_idle);

	HPmae = NewGO<prefab::CSpriteRender>(0);
	HPmae->Init(L"sprite/HPmae.dds", 150.0f, 100.0f);
	HPmae->SetPosition(HPmaePos);
	HPusiro = NewGO<prefab::CSpriteRender>(0);
	HPusiro->Init(L"sprite/HPusiro.dds", 200.0f, 100.0f);
	HPusiro->SetPosition(HPusiroPos);
	m_skinModelRender->SetShadowCasterFlag(true);

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	return true;
}
void Player::Update()
{
	//camera = FindGO<Camera>("�J����");

	blink();

	float LStickx = pad.GetLStickXF();
	float LSticky = pad.GetLStickYF();
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();


	//�W�����v
	if (m_charaCon.IsJump()) {
		m_skinModelRender->PlayAnimation(enAnimationClip_jump, 0.3);
		//if (m_charaCon.IsOnGround()) {
		m_state = 0;
		//m_skinModelRender->PlayAnimation(enAnimationClip_idle,0.3);
	//}
	}
	else if (m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonA)) {
		m_state = 1;
		m_moveSpeed.y = 350.0f;
	}
	//��������
	else if (m_moveSpeed.LengthSq() > 30 * 30) {
		
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.3);
	}
	/*else if (m_moveSpeed.LengthSq() > 600 * 600 && m_state == 2) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.3);
	}*/
	////�_�b�V��
	//else if(m_charaCon.IsOnGround() && Pad(0).IsTrigger(enButtonB)){
	//	m_state = 2;
	//	m_moveSpeed += cameraForward * LSticky * 800.0f;
	//	m_moveSpeed += cameraRight * LStickx * 800.0f;
	//
	//	/*m_skinModelRender->PlayAnimation( enAnimationClip_run,0.3);*/
 //   }
	//�ҋ@
	else {
		m_state = 5;
		m_skinModelRender->PlayAnimation(enAnimationClip_idle); //��
	}


	EnemyColider();

	//GhostObj();

	cameraForward.y = 0.0;
	cameraForward.Normalize();
	cameraRight.y = 0.0;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A
	m_moveSpeed.x = 0.0;
	m_moveSpeed.z = 0.0;

	m_moveSpeed += cameraForward * LSticky * 200.0f;
	m_moveSpeed += cameraRight * LStickx * 200.0f;

	
	////�����x�̌v�Z
	//CVector3 accForwardXZ = MainCamera().GetForward();
	//CVector3 accRightXZ = MainCamera().GetRight();
	//accForwardXZ.y = 0.0f;
	//accForwardXZ.Normalize();
	//accRightXZ.y = 0.0f;
	//accRightXZ.Normalize();

	////���C�́B
	//CVector3 friction = m_moveSpeed;
	//if (m_charaCon.IsJump()) {
	//	//�W�����v���̖��C�́B
	//	friction *= -1.0f;
	//}
	//else {
	//	friction *= -3.0f;
	//}
	//m_moveSpeed.x += friction.x * GameTime().GetFrameDeltaTime();
	//m_moveSpeed.z += friction.z * GameTime().GetFrameDeltaTime();

	////�����x��������B
	//m_moveSpeed += accForwardXZ;
	//m_moveSpeed += accRightXZ;

	////�d��
	//m_moveSpeed.y -= 900.0 * GameTime().GetFrameDeltaTime();
	//if (m_charaCon.IsJump()) {
	//	//�ړ����x�ɐ�����������B
	//	//�W�����v���ɃW�����v�O��葁���Ȃ邱�Ƃ͂Ȃ�
	//	CVector3 moveSpeedXZ = CVector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

	//	if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
	//		moveSpeedXZ.Normalize();
	//		moveSpeedXZ *= m_moveSpeedWhenStartJump;
	//		m_moveSpeed.x = moveSpeedXZ.x;
	//		m_moveSpeed.z = moveSpeedXZ.z;
	//	}
	//}

	////���ʂɃ��[���h�s������ƁE�E�E
	//CMatrix mWorld;
	//mWorld.MakeTranslation(m_position);
	////���̃��[���h�s�����Z���āA�q���ɉe����^���Ă݂�
	//mWorld.Mul(mWorld, parent->GetWorldMatrix());
	////�s������f���ɐݒ肷��
	//m_skinModelRender->(mWorld);

	//�d��
	m_moveSpeed.y -= 900.0 * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����

	//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
	/*CVector3 pos = m_position;
	pos.y += 30;
	m_ghostobj.SetPosition(pos);*/

	m_skinModelRender->SetPosition(m_position);//�v���C���[�Ɉړ���������

	Turn();

	HPUI();

	

	//3dMax��Ő����̐ݒ肳��Ă���̂ŉ�]����
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	qRot.Multiply(m_rotation, qRot);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
}
void Player::Turn()
{
	//Player�̉�]
	if (fabsf(m_moveSpeed.x) < 0.001f && 
		fabsf(m_moveSpeed.z) < 0.001f ){
		return;
	}
	//�p�x�����߂Ă���
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	//Z����]
	m_rotation.SetRotation(CVector3::AxisZ, -angle);
}
void Player::HPUI()
{
	//HP
	wchar_t text[256];
	swprintf(text, L"%02d / 10", HP);

	font->SetText(text);
	font->SetPosition({ 400, 250 });

	if (HP <= 5) {
		font->SetColor(color);
	}
}
void Player::blink()
{
	//�_�ŏ���
	if (muteki == true) {
		mutekitime++;
		const int Inbizible = 3;

		if ((mutekitime / Inbizible) % 2 == 0) {
			m_skinModelRender->SetActiveFlag(false);
		}
		else {
			m_skinModelRender->SetActiveFlag(true);
		}

		if (mutekitime >= 100 ) {
			m_skinModelRender->SetActiveFlag(true);
			muteki = false;
			mutekitime = 0;
		}
	}
}
void Player::Coinget()
{
	//�R�C�����ł����炱���ɏ���
	//�ᕶ
	/*
	if(�R�C���ƃv���C���[�̋��� <= 50){
	count++;
	DeleteGO(���������R�C��);
	}
	*/
}
void Player::EnemyColider()
{
	QueryGOs<Enemy2>("�G2", [&](Enemy2 * en2)->bool {
		CVector3 diff2 = m_position - en2->GetPosi();
		m_goal = Game::GetInstance()->m_goal;
		//����25�O�ギ�炢
		if (diff2.Length() < 25 && m_goal->GetClearFlag() == false
			&& HP > 0 && muteki == false) {
			//HP�_���[�W
			HP--;
			//pl->HPmae.x - Tidimaru.x;
			//���G
			muteki = true;
		}
		return true;
	});
	//HP�_���[�W
	QueryGOs<Enemy1>("�G1", [&](Enemy1 * en1)->bool {
	
			m_goal = Game::GetInstance()->m_goal;
			CVector3 diff1 = m_position - en1->GetPosi();
			
			//�����������Ȃ�����
			//����25�O�ギ�炢
			if (diff1.Length() < 28 && m_goal->GetClearFlag() == false
				&& HP > 0 && muteki == false) {
				//HP�_���[�W
				HP--;
				//pl->HPmae.x - Tidimaru.x;
				//���G
				muteki = true;
			}
			
		return true;
	});
}
void Player::GhostObj()
{
	m_en1 = Game::GetInstance()->m_en1;
	//�S�[�X�g�I�u�W�F�N�g�̓����蔻��(�G1)
	PhysicsWorld().ContactTest(m_en1->m_EnemyCharaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject) && muteki == false) {
			//���񂾂���
			HP--;
			muteki = true;
			m_en1->SetMoveSpeed({ 0,200,0 });
			//DeleteGO(this); //����������j��
		}
		else if (m_ghostobj.IsSelf(contactObject) && muteki == true) {
			m_en1->SetMoveSpeed({ 0,200,0 });
		}
	});
}