#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// packman�N���X
/// </summary>

namespace
{
	const float PLAYER_MOVE_SPEED{ 1.0f };
}
class Player :
    public GameObject
{
	int hModel_;
	float speed_; //�v���C���[�̃X�s�[�h
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED} {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

