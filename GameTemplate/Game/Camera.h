#pragma once
//#include <Player.h>
class Player;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	CVector3 GetCameraTargetPos()
	{
		return target;
	}
	CVector3 GetcamePos()
	{
		return camePos;
	}
private:
	//CVector3 m_position = CVector3::Zero; //���W
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 target;
	CVector3 camePos;//���W
	Player* m_player = nullptr;
	//�N���X�̌p��
	//�|�C���g�^
};

