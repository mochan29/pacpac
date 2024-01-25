#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
	int hModel_;
public:
	Player(GameObject* parent) :GameObject(parent, "Player"), hModel_(-1){};
	~Player() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
	void OnCollision(GameObject* pTarget) override;
};

