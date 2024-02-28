#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Apple.h"

/// <summary>
/// packman�N���X
/// </summary>

namespace
{
	const float PLAYER_MOVE_SPEED{ 0.1f };
}
class Player :
    public GameObject
{
	int hModel_; //�v���C���[�̃��f���ԍ�
	float speed_; //�v���C���[�̃X�s�[�h
	Stage* pStage_; //stage������Ă��邽�߂̃|�C���^
	int hpMax_; //�ő�lHP
	int hpCrr_; //���݂�HP

public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED},pStage_(nullptr), hpMax_(100), hpCrr_(100) {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	void OnCollision(GameObject* pTarget) override;
};

