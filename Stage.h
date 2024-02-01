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
/// 
enum STAGE_OBJ
{
	FLOOR, WALL,
};


class Stage:
    public GameObject
{
	int hFloor_; //床のモデル番号
	int hWall_; //床+壁のモデル番号
	std::vector<std::vector<int>> stage; //ステージ構成の二次元配列
	int stageWidth_; //ステージの幅
	int stageHeight_; //ステージの高さ
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//ステージの幅/高さを与える
	int GetStageWidth() { return stageWidth_;}
	int GetStageHeight() { return stageHeight_;}
	
	//ステージが壁かどうか判別
	bool isWall(int _x, int _y) ;
};

