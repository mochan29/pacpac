#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

/// <summary>
/// packmanクラス
/// </summary>

namespace
{
	const float PLAYER_MOVE_SPEED{ 0.1f };
}
class Player :
    public GameObject
{
	int hModel_; //プレイヤーのモデル番号
	float speed_; //プレイヤーのスピード
	Stage* pStage_; //stageを取ってくるためのポインタ
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1), speed_{PLAYER_MOVE_SPEED},pStage_(nullptr) {};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

