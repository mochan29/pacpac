#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// Enemy�N���X
/// </summary>

namespace
{
	const float ENEMY_MOVE_SPEED{ 0.03f };
}
class Enemy :
    public GameObject
{
	int hModel_; //�G�l�~�[�̃��f���ԍ���
	int hModel2_; //�G�l�~�[�̃��f���ԍ���
	float speed_; //�G�l�~�[�̃X�s�[�h
	Player* pPlayer_; //player������Ă��邽�߂̃|�C���^
	Stage* pStage_;
	int ranColor_; //�F�ς��p
public:
	Enemy(GameObject* parent) :GameObject(parent, "Enemy"), hModel_(-1), speed_{ ENEMY_MOVE_SPEED }, pPlayer_(nullptr),pStage_(nullptr),a(0){};
	~Enemy() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	void OnCollision(GameObject* pTarget) override;
};

