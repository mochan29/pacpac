#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ƒJƒƒ‰ƒNƒ‰ƒX
/// </summary>

class StageCamera :
	public GameObject
{
public:
	StageCamera(GameObject* parent) :GameObject(parent, "Camera"){};
	~StageCamera() {};
	void Initialize() override;
	void Update() override {};
	void Draw() override {};
	void Release() override {};
};

