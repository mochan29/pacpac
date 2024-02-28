#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Stage.h"

/// <summary>
/// Apple�N���X
/// </summary>

class Apple :
	public GameObject
{
	bool get_;
	int hModel_; //�G�l�~�[�̃��f���ԍ�
	Stage* pStage_;
public:
	Apple(GameObject* parent) :GameObject(parent, "Apple"), hModel_(-1), pStage_(nullptr), get_(false) {};
	~Apple() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};
