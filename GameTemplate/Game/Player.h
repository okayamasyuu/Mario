#pragma once
#include <Camera.h>
class Camera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Turn();
	void HPUI();
	void blink();
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
	}
	CVector3 GetPosi()
	{
		return m_position;
	}
	int GetHP()
	{
		return HP;
	}
	void HikuHP(int hp)
	{
		HP -= hp;
	}
	void SetMutekiFlag(bool mutekiflag)
	{
		muteki = mutekiflag;
	}
	bool GetMutekiFlag()
	{
		return muteki;
	}
	//���G����
	void TasuMutekiTime(int timer)
	{
		mutekitime += timer;
	}
	int GetMutekiTime()
	{
		return mutekitime;
	}
	void SetMutekiTime(int timer)
	{
		mutekitime = timer;
	}
	CCharacterController m_charaCon; //�L�����N�^�[�R���g���[���[
	CPad& pad = Pad(0);
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,   //�����A�j���[�V����
		enAnimationClip_jump,   //�W�����v�A�j���[�V����
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
private:
	int m_state = 0; //��Ԃ̕ϐ�
	int HP = 3;
	bool  muteki = false;
	int mutekitime = 0;
	prefab::CFontRender* font = nullptr; //�t�H���g
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CAnimationClip m_animClips[enAnimationClip_Num];
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	
	Camera* camera = nullptr;
};

