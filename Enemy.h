#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// Enemyクラス
/// </summary>

namespace
{
	const float ENEMY_MOVE_SPEED{ 0.03f };
}
class Enemy :
    public GameObject
{
	int hModel_; //エネミーのモデル番号紫
	int hModel2_; //エネミーのモデル番号青
	float speed_; //エネミーのスピード
	Player* pPlayer_; //playerを取ってくるためのポインタ
	Stage* pStage_;
	int ranColor_; //色変え用
public:
	Enemy(GameObject* parent) :GameObject(parent, "Enemy"), hModel_(-1), speed_{ ENEMY_MOVE_SPEED }, pPlayer_(nullptr),pStage_(nullptr),a(0){};
	~Enemy() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	void OnCollision(GameObject* pTarget) override;
};

