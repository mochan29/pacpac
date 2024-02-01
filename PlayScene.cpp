#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "StageCamera.h"

void PlayScene::Initialize()
{
	Instantiate<StageCamera>(this);
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}
