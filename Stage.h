#pragma once
#include "Engine/GameObject.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;


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
	ifstream inputFile_;
	string fname_ = "stage.csv";
	vector<string>inputList;
	vector<vector<int>> stage;
public:
	Stage(GameObject* parent) :GameObject(parent, "Stage"),hFloor_(-1),hWall_(-1) {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

