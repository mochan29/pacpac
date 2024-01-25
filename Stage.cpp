#include "Stage.h"
#include "Engine/Model.h"

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hWall_ >= 0);

	for (int x = 0; x < FLOORX; x++)
	{
		for (int z = 0; z < FLOORZ; z++)
		{
			stage[x][z] = 0;//?
		}
	}

	inputFile_.open(fname_, std::ios::in);
	if (inputFile_.fail())
	{
		exit(0);
	}

	string oneline;
	while (getline(inputFile_, oneline))
	{
		inputList.push_back(oneline);
	}

	for (int x = 0; x < FLOORX; x++)
	{
		for (int z = 0; z < FLOORZ; z++)
		{
			if(inputList[x][z]!=',')
			stage[x][z]=inputList[x][z] - '0';//stage‚ð‰Šú‰»‚µ‚Ä‚©‚ç‚¢‚ê‚È‚¢‚Æ‚¾‚ß‚ç‚µ‚¢
		}
	}

}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	Transform wallTrans;
	/*for (int z = 0; z < FLOORZ; z++)
	{
		for (int x = 0; x <FLOORX; x++)
		{
			floorTrans.position_ = { float(x - 5),0,float(z - 5)};
			wallTrans.position_ = { float(x - 5),0,float(z - 5)};
			Model::SetTransform(hFloor_, floorTrans);
			Model::SetTransform(hWall_, wallTrans);
			if (z == 0 || z == FLOORZ-1||x == 0||x ==FLOORX-1)
			{
				Model::Draw(hWall_);
			}
			else
			{
				Model::Draw(hFloor_);
			}
		}
	}*/

	for (int x = 0; x < FLOORX; x++)
	{
		for (int z = 0; z < FLOORZ; z++)
		{
			floorTrans.position_ = { float(x - 5),0,float(z - 5) };
			wallTrans.position_ = { float(x - 5),0,float(z - 5) };
			Model::SetTransform(hFloor_, floorTrans);
			Model::SetTransform(hWall_, wallTrans);
			if (stage[x][z]==0)
			{
				Model::Draw(hWall_);
			}
			else
			{
				Model::Draw(hFloor_);
			}
		}
	}

}
