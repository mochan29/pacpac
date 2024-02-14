#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// enemy�N���X
/// </summary>

namespace
{
	const float ENEMY_MOVE_SPEED{ 0.05f };
}
class Enemy :
    public GameObject
{
	int hModel_; //�v���C���[�̃��f���ԍ�
	float speed_; //�v���C���[�̃X�s�[�h
	Player* pPlayer_; //player������Ă��邽�߂̃|�C���^
	Stage* pStage_;
public:
	Enemy(GameObject* parent) :GameObject(parent, "Enemy"), hModel_(-1), speed_{ ENEMY_MOVE_SPEED }, pPlayer_(nullptr),pStage_(nullptr){};
	~Enemy() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	void OnCollision(GameObject* pTarget) override;
};
