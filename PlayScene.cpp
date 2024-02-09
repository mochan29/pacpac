#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "StageCamera.h"
#include "Gauge.h"
#include "Enemy.h"

void PlayScene::Initialize()
{
	Instantiate<StageCamera>(this);
	Instantiate<Stage>(this);
	Instantiate<Gauge>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

