#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 体力ゲージのクラス
/// </summary>

class Gauge :
    public GameObject
{
	int hGaugeBar_; //ゲージの画像番号
	int hGaugeFrame_; //フレームの画像番号
	int gaugeMaxVal_; //ゲージの最大値
	int gaugeCrrVal_; //ゲージの現在の値
public:
	Gauge(GameObject* parent) :GameObject(parent, "Gauge"),hGaugeBar_(-1),hGaugeFrame_(-1),gaugeMaxVal_(200),gaugeCrrVal_(100){};
	~Gauge() {};
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override {};

	//ゲージの最大値と現在の値を与える
	void SetGaugeVal(int _max, int _crr) { gaugeMaxVal_ = _max; gaugeCrrVal_ = _crr; }
};

