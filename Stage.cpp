#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent) :GameObject(parent, "Stage"), hFloor_(-1), hWall_(-1)
{
#if 0
	//�t�@�C����ǂݍ���
	std::vector<std::string>inputList;
	stage.assign(FLOORX, std::vector<int>(FLOORZ, 0));

	inputFile_.open(fname_, std::ios::in);
	if (inputFile_.fail())
	{
		exit(0);
	}

	std::string oneline;
	std::string oneline2;
	std::vector<std::string>inputList2;
	while (std::getline(inputFile_, oneline))
	{
		inputList.push_back(oneline);//��s�Ƃ��Ă���
	}

	for (int i = 0; i < inputList.size(); i++)
	{
		std::stringstream inputList; //ss�l�ɕϊ� ??
		while (std::getline(inputList, oneline2, ','))//������
		{
			inputList2.push_back(oneline2);//,�Ȃ���̔z������
		}
	}

	std::vector<int> inList;
	for (int i = 0; i < inputList2.size(); i++)
	{
		inList[i] = stoi(inputList2[i]);//int�ɕϊ�
	}

	//�X�e�[�W�̔z��ɓ˂�����
	for (int i = 0; i < inList.size(); i++)
	{
		stage.push_back(inList);//���̂�ɓ˂�����
	}
#endif

	stage={ 
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },		
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, };
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
	Transform wallTrans;

	//�X�e�[�W������
	for (int y = 0; y < FLOORY; y++)
	{
		for (int x = 0; x < FLOORX; x++)
		{
			floorTrans.position_ = { float(x-5),0,float(y-5) };
			wallTrans.position_ = { float(x-5),0,float(y-5) };

			if (stage[y][x]==1)
			{
				Model::SetTransform(hWall_, wallTrans);
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
