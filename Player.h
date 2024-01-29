#pragma once
#include "Engine/GameObject.h"

namespace
{
	const float PLAYER_MOVE_SPEED{ 0.1f };
}
class Player :
    public GameObject
{
	int hModel_;
	float speed_;
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED} {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
	void OnCollision(GameObject* pTarget) override;
};

