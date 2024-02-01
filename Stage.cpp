#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Stage::Stage(GameObject* parent) :GameObject(parent, "Stage"), hFloor_(-1), hWall_(-1)
{
	CsvReader csv;
	csv.Load("stage.csv");

	stageWidth_ = csv.GetWidth();
	stageHeight_ = csv.GetHeight();

	for (int i = 0; i < stageHeight_; i++)
	{
		std::vector<int> sdata(stageWidth_, 0);
		stage.push_back(sdata);
	}

	for (int y = 0; y < stageHeight_; y++)
	{
		for (int x = 0; x < stageWidth_; x++)
		{
			stage[y][x] = csv.GetValue(x, y);
		}
	}
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hWall_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	for (int y = 0; y < stageHeight_; y++)
	{
		for (int x = 0; x < stageWidth_; x++)
		{
			floorTrans.position_ = { (float)x,0,(float)14-y };

			if (stage[y][x]==1)
			{
				Model::SetTransform(hWall_, floorTrans);
				Model::Draw(hWall_);
			}
			else
			{
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
	//‰¡‚Ì‚¨‘|œ
	for (int i = 0; i < stageHeight_; i++)
	{
		stage[i].clear();
	}
	//c‚Ì‚¨‘|œ
	stage.clear();
}

bool Stage::isWall(int _x, int _y)
{
	if (stage[_y][_x] == STAGE_OBJ::WALL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
