#pragma once
#include "Engine/GameObject.h"
class TitleScene :
	public GameObject
{
	int hImage_;
public:
	TitleScene(GameObject* parent) :GameObject(parent, "TitleScene"), hImage_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};
