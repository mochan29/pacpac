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
/// 
enum STAGE_OBJ
{
	FLOOR, WALL,
};


class Stage:
    public GameObject
{
	int hFloor_; //���̃��f���ԍ�
	int hWall_; //��+�ǂ̃��f���ԍ�
	std::vector<std::vector<int>> stage; //�X�e�[�W�\���̓񎟌��z��
	int stageWidth_; //�X�e�[�W�̕�
	int stageHeight_; //�X�e�[�W�̍���
public:
	Stage(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�X�e�[�W�̕�/������^����
	int GetStageWidth() { return stageWidth_;}
	int GetStageHeight() { return stageHeight_;}
	
	//�X�e�[�W���ǂ��ǂ�������
	bool isWall(int _x, int _y) ;
};

