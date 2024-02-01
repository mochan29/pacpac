#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Camera.h"

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Camera::SetPosition({ 0,9,-10 });
	Camera::SetTarget({ 0,0,0 });
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}
