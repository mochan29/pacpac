#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "StageCamera.h"
#include "Gauge.h"
#include "Enemy.h"
#include "Apple.h"

void PlayScene::Initialize()
{
	enemyNum_ = ENEMYNUM;
	appNum_ = APPNUM;
	Instantiate<StageCamera>(this);
	Instantiate<Stage>(this);
	Instantiate<Gauge>(this);
	Instantiate<Player>(this);
	for (int i = 0; i < enemyNum_; i++)
	{
		Instantiate<Enemy>(this);
	}
	for (int i = 0; i < appNum_; i++)
	{
		Instantiate<Apple>(this);
	}
}

