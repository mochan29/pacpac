#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Apple.h"

/// <summary>
/// Playerクラス
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
	int hModel_; //プレイヤーのモデル番号
	float speed_; //プレイヤーのスピード
	Stage* pStage_; //stageを取ってくるためのポインタ
	int hpMax_; //最大値HP
	int hpCrr_; //現在のHP
	int appCnt_; //エサを取った数
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

