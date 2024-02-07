#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �̗̓Q�[�W�̃N���X
/// </summary>

class Gauge :
    public GameObject
{
	int hGaugeBar_; //�Q�[�W�̉摜�ԍ�
	int hGaugeFrame_; //�t���[���̉摜�ԍ�
	int gaugeMaxVal_; //�Q�[�W�̍ő�l
	int gaugeCrrVal_; //�Q�[�W�̌��݂̒l
public:
	Gauge(GameObject* parent) :GameObject(parent, "Gauge"),hGaugeBar_(-1),hGaugeFrame_(-1),gaugeMaxVal_(200),gaugeCrrVal_(100){};
	~Gauge() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	//�Q�[�W�̍ő�l�ƌ��݂̒l��^����
	void SetGaugeVal(int _max, int _crr) { gaugeMaxVal_ = _max; gaugeCrrVal_ = _crr; }
};

