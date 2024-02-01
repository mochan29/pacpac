#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

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
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED},pStage_(nullptr) {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

