#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// packmanクラス
/// </summary>

namespace
{
	const float PLAYER_MOVE_SPEED{ 1.0f };
}
class Player :
    public GameObject
{
	int hModel_;
	float speed_; //プレイヤーのスピード
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED} {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

