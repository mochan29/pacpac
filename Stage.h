#pragma once
#include "Engine/GameObject.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
	const int FLOORX = 15;
	const int FLOORZ = 15;
}


class Stage:
    public GameObject
{
	int hFloor_;
	int hWall_;
	std::ifstream inputFile_;
	std::string fname_ = "stage.csv";

	std::vector<std::vector<int>> stage;
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

