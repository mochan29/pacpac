#pragma once
#include "Engine/GameObject.h"
class ClearScene :
	public GameObject
{
	int hImage_;
public:
	ClearScene(GameObject* parent) :GameObject(parent, "ClearScene"), hImage_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};
