#include "Stage.h"
#include "Engine/Model.h"
void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\floor.fbx");
	assert(hFloor_ >= 0);

}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	for (int z = 0; z < 15; z++)
	{
		for (int x = 0; x < 15; x++)
		{
			floorTrans.position_ = {float(x-5),0,float(z-5) };
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}
}
