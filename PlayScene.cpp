#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "StageCamera.h"
#include "Gauge.h"

void PlayScene::Initialize()
{
	Instantiate<StageCamera>(this);
	Instantiate<Stage>(this);
	Instantiate<Gauge>(this);
	Instantiate<Player>(this);

}

