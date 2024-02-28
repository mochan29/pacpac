#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Apple.h"

/// <summary>
/// Player�N���X
/// </summary>

namespace
{
	const float PLAYER_MOVE_SPEED=0.1f;
	const int AppleNum = 2;
	const float UP_DEGREE = 90.0f;
	const int DEFUP = 90;
	const int DEFDOWN = 270;
	const int DEFRIGHT = 0;
	const int DEFLEFT = 180;
	const int BOUNS = 10;
}

class Player :
    public GameObject
{
	int hModel_; //�v���C���[�̃��f���ԍ�
	float speed_; //�v���C���[�̃X�s�[�h
	Stage* pStage_; //stage������Ă��邽�߂̃|�C���^
	int hpMax_; //�ő�lHP
	int hpCrr_; //���݂�HP
	int appCnt_; //�G�T���������
	int degree_;

public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED},pStage_(nullptr), hpMax_(100), hpCrr_(100),appCnt_(0),degree_(0){};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	void OnCollision(GameObject* pTarget) override;
};

