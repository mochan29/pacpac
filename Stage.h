#pragma once
#include "Engine/GameObject.h"

namespace
{
	const int FLOORZ = 15;
	const int FLOORX = 15;
}

class Stage :
    public GameObject
{
	int hFloor_;
	int hWall_;
public:
	Stage(GameObject* parent) :GameObject(parent, "Stage"),hFloor_(-1),hWall_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

