#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �v���C�V�[�����܂Ƃ߂�N���X
/// </summary>
/// 
class PlayScene :
    public GameObject
{
public:
	PlayScene(GameObject* parent) :GameObject(parent, "PlayScene"){};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

