#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// プレイシーンをまとめるクラス
/// </summary>

 namespace
{
	int ENEMYNUM = 2;
	int APPNUM = 2;
}

class PlayScene :
    public GameObject
{
	int enemyNum_ ;
	int appNum_;
public:
	PlayScene(GameObject* parent) :GameObject(parent, "PlayScene"),enemyNum_(0),appNum_(0){};
	void Initialize() override;
	void Update() override {};
	void Draw() override {};
	void Release() override {};
};

