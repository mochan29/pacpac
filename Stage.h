#pragma once
#include "Engine/GameObject.h"
class Stage :
    public GameObject
{
	int hFloor_;
public:
	Stage(GameObject* parent) :GameObject(parent, "Stage"),hFloor_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

