#pragma once

#include "Engine/GameObject.h"
class OverScene :
	public GameObject
{
	int hImage_;
public:
	OverScene(GameObject* parent) :GameObject(parent, "OverScene"), hImage_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

