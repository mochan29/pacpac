#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �J�����N���X
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

