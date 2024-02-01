#pragma once
#include "Engine/GameObject.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// �X�e�[�W�̃N���X
/// </summary>

namespace
{
	const int FLOORX = 15;
	const int FLOORY = 15;
}


class Stage:
    public GameObject
{
	int hFloor_; //���̃��f���ԍ�
	int hWall_; //��+�ǂ̃��f���ԍ�
	std::ifstream inputFile_; //�ǂ�ł����t�@�C��
	std::string fname_ = "stage.csv";

	std::vector<std::vector<int>> stage; //�X�e�[�W�\���̓񎟌��z��
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

