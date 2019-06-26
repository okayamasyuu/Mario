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
	void SetPosi(CVector3 Plposi)
	{
		m_position = Plposi;
	}
	CVector3 GetPosi()
	{
		return m_position;
	}
	CPad& pad = Pad(0);
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,   //�����A�j���[�V����
		enAnimationClip_jump,   //�W�����v�A�j���[�V����
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
private:
	
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CAnimationClip m_animClips[enAnimationClip_Num];
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_charaCon; //�L�����N�^�[�R���g���[���[
	Camera* camera = nullptr;
};

