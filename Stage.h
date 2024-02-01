#pragma once
#include "Engine/GameObject.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// ステージのクラス
/// </summary>

namespace
{
	const int FLOORX = 15;
	const int FLOORY = 15;
}


class Stage:
    public GameObject
{
	int hFloor_; //床のモデル番号
	int hWall_; //床+壁のモデル番号
	std::ifstream inputFile_; //読んできたファイル
	std::string fname_ = "stage.csv";

	std::vector<std::vector<int>> stage; //ステージ構成の二次元配列
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};
};

