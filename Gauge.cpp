#include "Gauge.h"
#include "Engine/Image.h"

void Gauge::Initialize()
{
	hGaugeBar_ = Image::Load("Image\\waku.png");
	assert(hGaugeBar_ >= 0);
	hGaugeFrame_ = Image:: Load("Image\\gauge.png");
	assert(hGaugeFrame_ >=0);

	transform_.position_.x =-0.9f;
	transform_.position_.y=0.9f;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	Transform tr = transform_;
	tr.scale_.x = (float)gaugeCrrVal_ / (float)gaugeMaxVal_;
	Image::SetTransform(hGaugeFrame_, tr);
	Image::Draw(hGaugeFrame_);
	Image::SetTransform(hGaugeBar_, transform_);
	Image::Draw(hGaugeBar_);

	
}
