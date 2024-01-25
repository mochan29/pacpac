#include "Stage.h"
#include "Engine/Model.h"

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
	Transform wallTrans;
	for (int z = 0; z < FLOORZ; z++)
	{
		for (int x = 0; x <FLOORX; x++)
		{
			floorTrans.position_ = { float(x - 5),0,float(z - 5) };
			wallTrans.position_ = { float(x - 5),0,float(z - 5) };
			Model::SetTransform(hFloor_, floorTrans);
			Model::SetTransform(hWall_, wallTrans);
			Model::Draw(hFloor_);
			if (z == 0 || z == FLOORZ-1||x == 0||x ==FLOORX-1)
			{
				Model::Draw(hWall_);
			}
		}
	}
}
